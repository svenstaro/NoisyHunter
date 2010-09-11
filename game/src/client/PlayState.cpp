#include "PlayState.hpp"
#include "Root.hpp"
#include "Entity.hpp"
#include <boost/foreach.hpp>
#include <iostream>

PlayState::PlayState() {}
PlayState::~PlayState() {}

void PlayState::Initialize(){
    // load resources

    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gfx"),
                                                                           "submarine1.svg", 80, 53, "submarine");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gfx"),
                                                                           "aim.svg", 80, 53, "aim");

    // create GUI

    // create entities
    mPlayerSubmarine = new Submarine(0.5,0.5);
    AddEntity(mPlayerSubmarine);
    mPlayerSubmarine->SetTarget(Engine::Vector2D(1,1));

    mCrosshair = new Crosshair();
    AddEntity(mCrosshair);


    Engine::InputManager* in = Engine::Root::get_mutable_instance().GetInputManagerPtr();
    // bind keys
    Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnLeaveGame, this);
    in->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
    // bind mouse
    Engine::MouseBindingCallback mcb = boost::bind(&PlayState::OnClick, this, _1);
    in->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
    Engine::MouseBindingCallback right = boost::bind(&PlayState::OnRightClick, this, _1);
    in->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

    // mouse cursor
    Engine::MouseBindingCallback mv = boost::bind(&PlayState::OnMouseMove, this, _1);
    in->BindMouse(mv, Engine::MOUSE_MOVED);
    // hide original cursor
    Engine::Root::get_mutable_instance().SetMouseHidden(true);



}
void PlayState::Shutdown(){
    // hm, what do we need shutdown for!?
}

void PlayState::Update(float time_delta){
    UpdateAllEntities(time_delta);

    // TODO: Networking
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->PreparePacket();
    BOOST_FOREACH(Engine::Entity& entity, mEntities){
        if (entity.GetLayer() == Engine::Entity::LAYER_REGULAR){
            Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->AddEntity(entity);
        }
    }
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket();

}



void PlayState::OnSetNoisyMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);

    mPlayerSubmarine->SetTarget(target);
}

void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position){
    /*const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);
    AddEntity(torpedo);*/
}

void PlayState::OnLeaveGame() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
void PlayState::OnClick(Engine::MouseEventArgs args){
    OnNavigateTo(args);
}
void PlayState::OnRightClick(Engine::MouseEventArgs args){
    OnFireTorpedo(args);
}
void PlayState::OnMouseMove(Engine::MouseEventArgs args){
    mCrosshair->SetPosition(args.X, args.Y);
}
