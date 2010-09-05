#include "PlayState.hpp"
#include "Root.hpp"
#include "Entity.hpp"
#include <boost/foreach.hpp>

PlayState::PlayState() {}
/*PlayState::PlayState(Engine::Root* root){
    mRoot = root;
}*/
PlayState::~PlayState() {}

void PlayState::Initialize(){
    // create GUI

    // create entities

    // bind keys
    Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnLeaveGame, this);
    Engine::Root::get_mutable_instance().GetInputMangerPtr()->BindKey( sf::Key::Escape, sf::Event::KeyPressed, cb );
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
    //const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    //mPlayerSubmarine->SetTarget(target);
}
void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);

    AddEntity(torpedo);
}

void PlayState::OnLeaveGame() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
