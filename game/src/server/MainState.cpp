#include "MainState.hpp"
#include "Root.hpp"

MainState::MainState() {
}

MainState::~MainState() {
}

void MainState::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing main state.");
    
    // Bind connection events
    auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
    netmgr->BindOnClientConnected(boost::bind(&MainState::OnClientConnected, this, _1));
}
void MainState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down main state.");
}

void MainState::Update(float time_delta) {
    //Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->Receive();
}

void MainState::OnClientConnected(std::string client_name) {
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	auto clientmgr = netmgr->GetClientManagerPtr();
	sf::Uint16 cl_id = clientmgr->GetId(client_name);
	float lol = sf::Randomizer::Random(0.1f, 0.9f);
	Submarine* submarine = new Submarine(lol, lol, cl_id);
	netmgr->SendEntityAdd(submarine);
	AddEntity(submarine);
}
