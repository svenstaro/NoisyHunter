#include "MainWorld.hpp"
#include "Root.hpp"

MainWorld::MainWorld() {
}

MainWorld::~MainWorld() {
}

void MainWorld::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_WORLD, "Initializing main world.");
    
	WorldPolygon* pol1 = new WorldPolygon();
	pol1->Initialize();
	pol1->GrabEntityEntityUniqueId();
	pol1->AddPoint(sf::Vector2f(0,0));
	pol1->AddPoint(sf::Vector2f(0.2,0.2));

	pol1->AddPoint(sf::Vector2f(0.8,0.4));
	pol1->AddPoint(sf::Vector2f(1.8,0.2));
	pol1->AddPoint(sf::Vector2f(1.7,0.6));
	pol1->AddPoint(sf::Vector2f(1.5, 0.64));
	pol1->AddPoint(sf::Vector2f(1.8,1.4));
	pol1->AddPoint(sf::Vector2f(1.2,1.94));
	pol1->AddPoint(sf::Vector2f(0.24,1.34));
	pol1->AddPoint(sf::Vector2f(0.06,0.4));

	pol1->AddPoint(sf::Vector2f(0.2,0.2));
	pol1->AddPoint(sf::Vector2f(0,0));
	pol1->AddPoint(sf::Vector2f(2,0));
	pol1->AddPoint(sf::Vector2f(2,2));
	pol1->AddPoint(sf::Vector2f(0,2));

	pol1->SetPosition(0,0);
	AddEntity(pol1);

	// rock
	WorldPolygon* pol2 = new WorldPolygon();
	pol2->Initialize();
	pol2->GrabEntityEntityUniqueId();
	pol2->AddPoint(sf::Vector2f(1.2,0.95));
	pol2->AddPoint(sf::Vector2f(1.3,1.1));
	pol2->AddPoint(sf::Vector2f(1.1,1.05));
	pol2->AddPoint(sf::Vector2f(1.05,0.9));
	pol2->AddPoint(sf::Vector2f(1.12,0.86));

	pol2->SetPosition(0,0);
	AddEntity(pol2);
}

void MainWorld::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {
	// handle different interactions here!!
	if(interaction_id == INTERACTION_SETSUBMARINETARGET) {
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_WORLD, "Received INTERACTION_SETSUBMARINETARGET.");
		float target_x, target_y;
		data >> target_x >> target_y;

		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			if(sub->GetClientId() == client_id) {
				sub->SetTarget(target_x, target_y);
			}
		}

	} else if(interaction_id == INTERACTION_FIRETORPEDO) {
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_WORLD, "Received INTERACTION_FIRETORPEDO.");
		float target_x, target_y, time_to_live;
		data >> target_x >> target_y >> time_to_live;
		// Get player submarine
		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			if(sub->GetClientId() == client_id) {
				Torpedo* torpedo = (Torpedo*)sub->FireTorpedoTo(Engine::Vector2D(target_x, target_y), time_to_live);
				torpedo->GrabEntityEntityUniqueId();
				auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
				netmgr->SendEntityAdd(*torpedo);
				AddEntity(torpedo);
			}
		}
	} else if(interaction_id == INTERACTION_FIRESONARPING) {
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_WORLD, "Received INTERACTION_FIRESONARPING.");
		float target_x, target_y, time_to_live;
		data >> target_x >> target_y >> time_to_live;

		// Get player submarine
		BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
			if(sub->GetClientId() == client_id) {
				SonarPing* sonarping = (SonarPing*)sub->FireSonarPing(Engine::Vector2D(target_x, target_y), time_to_live);
				sonarping->GrabEntityEntityUniqueId();
				auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
				netmgr->SendEntityAdd(*sonarping);
				AddEntity(sonarping);
			}
		}
	}
}
