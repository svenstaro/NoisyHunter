#include "MainState.hpp"
#include "Root.hpp"

MainState::MainState() {
}

MainState::~MainState() {
}

void MainState::Initialize() {
	Engine::LogManager* logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing main state.");
}
void MainState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down main state.");
}

void MainState::Update(float time_delta) {
    //Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->Receive();
}

void MainState::OnClientConnect(sf::Uint16 cl_id) {
	AddEntity(new Submarine(0.3, 0.4, cl_id));
}
