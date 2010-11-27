#include "MainWorld.hpp"
#include "Root.hpp"

MainWorld::MainWorld() {
}

MainWorld::~MainWorld() {
}

MainWorld* MainWorld::clone() const {
	return new MainWorld();
}

void MainWorld::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
    logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_WORLD, "Initializing main world."); 
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
				torpedo->GrabEntityUniqueId();
				//auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
				//netmgr->SendEntityAdd(*torpedo, mWorldUniqueId);
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
				sonarping->GrabEntityUniqueId();
				//auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
				//netmgr->SendEntityAdd(*sonarping, mWorldUniqueId);
				AddEntity(sonarping);
			}
		}
	}
}
sf::Uint16 MainWorld::GetWorldTypeId() const {
	return WORLDTYPEID_PLAYWORLD;
}
