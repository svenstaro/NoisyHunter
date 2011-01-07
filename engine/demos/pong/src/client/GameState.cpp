#include "GameState.hpp"
#include "Root.hpp"


GameState::GameState() {}
GameState::~GameState() {}

void GameState::Initialize() {
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing PlayState.");

    // GUI
    
    // KEYS
    auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
    Engine::KeyBindingCallback up = boost::bind(&GameState::OnPressUp, this);
    inputmgr->BindKey( up, Engine::KEY_PRESSED , sf::Key::Up );
	Engine::KeyBindingCallback down = boost::bind(&GameState::OnPressDown, this);
	inputmgr->BindKey( down, Engine::KEY_PRESSED , sf::Key::Down );
	Engine::KeyBindingCallback esc = boost::bind(&GameState::OnPressEscape, this);
	inputmgr->BindKey( esc, Engine::KEY_PRESSED , sf::Key::Escape );

    auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
    netmgr->SetEntityState(this);
    netmgr->ConnectToServer();
}

void GameState::Shutdown() {
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down PlayState.");

	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();
}

void GameState::Update(float time_delta) {
    UpdateAllEntities(time_delta);
    //debug messages here ;)
}


void GameState::OnPressUp() {
    
}
void GameState::OnPressDown() {

}
void GameState::OnPressEscape() {
	Engine::Root::get_mutable_instance().RequestShutdown();
}
