#include <iostream>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#include "PlayState.hpp"
#include "Root.hpp"
#include "Entity.hpp"

PlayState::PlayState() {}

PlayState::~PlayState() {}

void PlayState::Initialize() {
    // load resources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();
	resmgr->AddImage(boost::filesystem::path("../game/gfx"), 
					 "submarine1.svg", 80, 53, "submarine");
    resmgr->AddImage(boost::filesystem::path("../game/gfx"), 
					 "aim.svg", 80, 53, "aim");

    // create GUI
	// TODO: Do stuff

	// client side only entity
    mCrosshair = new Crosshair();
    AddEntity(mCrosshair);


    auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
    // bind keys
    Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnLeaveGame, this);
    inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
    // bind mouse
    Engine::MouseBindingCallback mcb = boost::bind(&PlayState::OnClick, this, _1);
    inputmgr->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
    Engine::MouseBindingCallback right = boost::bind(&PlayState::OnRightClick, this, _1);
    inputmgr->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

    // mouse cursor
    Engine::MouseBindingCallback mv = boost::bind(&PlayState::OnMouseMove, this, _1);
    inputmgr->BindMouse(mv, Engine::MOUSE_MOVED);
    // hide original cursor
    Engine::Root::get_mutable_instance().SetMouseHidden(true);
    
    // Bind connection events
    auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
    netmgr->BindOnClientConnected(boost::bind(&PlayState::OnClientConnected, this, _1));

    // create entities
	// TODO: NEXT TASK
    Submarine player_submarine(0.5,0.5);
    //AddEntity(mPlayerSubmarine);
    player_submarine.SetTarget(Engine::Vector2D(0.2,0.2));
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_ENTITYADD);
	packet << player_submarine.GetEntityId();
	Engine::IOPacket iopacket(false, packet);
	player_submarine.serialize(iopacket);
	packet = iopacket.GetPacket();
	netmgr->SendPacket(packet);
}

void PlayState::Shutdown() {
    // hm, what do we need shutdown for!?
}

void PlayState::Update(float time_delta) {
    UpdateAllEntities(time_delta);

    // TODO: Networking
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->PreparePacket();
    BOOST_FOREACH(Engine::Entity& entity, mEntities){
        if(entity.GetLayer() == Engine::Entity::LAYER_REGULAR){
            Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->AppendEntityToPacket(entity);
        }
    }
    
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket();

}

void PlayState::OnSetNoisyMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position) {
    //const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    //mPlayerSubmarine->SetTarget(target);

    
	// TODO: Send packets here. Next task.
//    sf::Packet p;
//    p << sf::Uint16(Engine::NETCMD_ENTITYACTION) << 0x01 << mPlayerSubmarine->GetUniqueId() << mouse_position.X << mouse_position.Y;
//    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(p);
//    std::cout << "Send action" << std::endl;
}

void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position) {
    /*const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);
    AddEntity(torpedo);*/
}

void PlayState::OnLeaveGame() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}

void PlayState::OnClick(Engine::MouseEventArgs args) {
    OnNavigateTo(args);
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendChatMessage("I am so glad I just clicked!");
}

void PlayState::OnRightClick(Engine::MouseEventArgs args) {
    OnFireTorpedo(args);
}

void PlayState::OnMouseMove(Engine::MouseEventArgs args) {
    mCrosshair->SetPosition(args.X, args.Y);
}

void PlayState::OnClientConnected(const std::string& client_name) {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "CLient connected: " + client_name);
    if (client_name == Engine::Root::get_mutable_instance().GetClientName()){
        logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "THAT'S YOU!!");
    }
}
