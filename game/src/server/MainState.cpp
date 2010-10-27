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

void MainState::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {
	// handle different interactions here!!
	if(interaction_id == INTERACTION_SETSUBMARINETARGET) {
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Received INTERACTION_SETSUBMARINETARGET.");
		float target_x, target_y;
		data >> target_x >> target_y;

		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			if(sub->GetClientId() == client_id) {
				sub->SetTarget(target_x, target_y);
			}
		}

	} else if(interaction_id == INTERACTION_FIRETORPEDO) {
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Received INTERACTION_FIRETORPEDO.");
		float target_x, target_y, time_to_live;
		data >> target_x >> target_y >> time_to_live;

		// Get player submarine
		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			if(sub->GetClientId() == client_id) {
				Torpedo* torpedo = (Torpedo*)sub->FireTorpedoTo(Engine::Vector2D(target_x, target_y), time_to_live);
				torpedo->GrabUniqueId();
				auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
				netmgr->SendEntityAdd(torpedo);
				AddEntity(torpedo);
			}
		}
	}
}

void MainState::Update(float time_delta) {
	UpdateAllEntities(time_delta);

	const sf::Uint16 time = Engine::Root::get_const_instance().GetRunTime();
	if(time % 3 and not mTargetSet) {
		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			Engine::Vector2D lolvec = { sf::Randomizer::Random(0.1f, 0.9f), sf::Randomizer::Random(0.1f, 0.9f) };
			//sub->SetTarget(lolvec);
		}
		mTargetSet = true;
		
	} else {
		mTargetSet = false;
	}
}

void MainState::OnClientConnected(sf::Uint16 client_id) {
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	auto clientmgr = netmgr->GetClientManagerPtr();
	sf::Uint16 cl_id = clientmgr->GetId(client_name);

	float lol = sf::Randomizer::Random(0.1f, 0.9f);
	Submarine* submarine1 = new Submarine(lol, lol, client_id);
	submarine1->GrabUniqueId();
	submarine1->SetClientId(client_id);

	SendAllEntityAddToClient(client_id);

	AddEntity(submarine1);			

	netmgr->SendEntityAdd(*submarine1);
}
