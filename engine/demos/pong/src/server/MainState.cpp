#include "MainState.hpp"
#include "Root.hpp"

MainState::MainState() {}
MainState::~MainState() {}

void MainState::Initialize() {
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "MainState initialized.");


	Ball* b = new Ball();
	b->Initialize(Engine::Vector2D(0.5f, 0.5f), Engine::Vector2D(0.01f, 0.01f), 0.02f);
	mWorlds.back().AddEntity(b);
    // TODO: Add paddles.

	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SetEntityState(this);
}

void MainState::Shutdown() {
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down MainState.");
}
