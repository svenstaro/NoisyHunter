#include <boost/foreach.hpp>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Root.hpp"

namespace Engine {

State::State() {}

State::~State() {}

void State::Shutdown() {}

void State::Update(const float time_delta) {
	UpdateAllEntities(time_delta);
}

void State::UpdateAllEntities(const float time_delta) {

	BOOST_FOREACH(Entity& entity, mEntities) {
		entity.Update(time_delta);
		if(Root::get_mutable_instance().IsServer()) {
			if(entity.GetLifeTime() >= entity.GetTimeToLive()) {
				entity.Deinit();
				mEntities.erase_if(boost::bind(&Entity::GetUniqueId, _1) == entity.GetUniqueId());
			}
		}
	}

	if(mEntityListNeedsSorting) {
		//mEntities.sort();
		mEntityListNeedsSorting = false;
	}

	BOOST_FOREACH(GuiSystem& system, mGuiSystems){
		system.Update(time_delta);
	}
}

void State::AppendAllEntitiesToPacket() {
	BOOST_FOREACH(Entity& entity, mEntities) {
		Root::get_mutable_instance().GetNetworkManagerPtr()->
			AppendEntityToPacket(entity);
	}
}

void State::Draw(sf::RenderTarget* target) {

	Root::get_mutable_instance().SetRenderMode(RENDERMODE_WORLD);
	BOOST_FOREACH(Entity& entity, mEntities) {
		entity.Draw(target);
	}

	Root::get_mutable_instance().SetRenderMode(RENDERMODE_GUI);
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.Draw(target);
	}
}

void State::HandleEvent(sf::Event e) {
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.HandleEvent(e);
	}
}

void State::AddEntity(Entity* entity) {
	mEntities.push_back(entity);
	mEntityListNeedsSorting = true;
}

void State::CreateGuiSystem() {
	mGuiSystems.push_back(new GuiSystem());
}

sf::Uint16 State::GetEntityCount() {
	return sf::Uint16(mEntities.size());
}

void State::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {}

Entity* State::GetEntityByUniqueId(const sf::Uint16 unique_id) {
   	BOOST_FOREACH(Entity& entity, mEntities) {
		if(entity.GetUniqueId() == unique_id) {
            return &entity;
        }
	} 
    return NULL;
}

void State::DeleteEntitiesByClientId(const sf::Uint16 client_id) {
	mEntities.erase_if(boost::bind(&Entity::GetClientId, _1) == client_id);
}

void State::DeleteEntityByUniqueId(const sf::Uint16 unique_id) {
	mEntities.erase_if(boost::bind(&Entity::GetUniqueId, _1) == unique_id);
}

void State::OnLeaveGame() {}


bool State::StatesBelowArePaused() {
	return true;
}

bool State::StatesBelowAreHidden() {
	return true;
}

bool State::IsCurrentState() {
	return Root::get_mutable_instance().GetStateManagerPtr()->IsCurrentState(this);
}

}
