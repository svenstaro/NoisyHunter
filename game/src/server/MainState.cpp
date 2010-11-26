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
	netmgr->SetEntityState(this);

	mAmountToPop = 0;
}

void MainState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down main state.");
}

void MainState::OnClientConnected(sf::Uint16 client_id) {
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();

	float lol = sf::Randomizer::Random(0.1f, 0.9f);
	Submarine* submarine1 = new Submarine();
	submarine1->SetPosition(Engine::Vector2D(lol, lol));
	submarine1->GrabEntityUniqueId();
	submarine1->SetClientId(client_id);
	sf::Uint16 world_unique_id = mWorlds.back().GetWorldUniqueId();

	GetWorld(world_unique_id)->AddEntity(submarine1);

	//netmgr->SendEntityAdd(*submarine1, world_unique_id);
}
