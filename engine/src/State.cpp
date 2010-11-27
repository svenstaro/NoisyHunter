#include <boost/foreach.hpp>

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Root.hpp"

namespace Engine {

State::State() {}

State::~State() {}

void State::Shutdown() {}

void State::AddWorld(World* world) {
	world->Initialize();
	world->InitializePhysics();
	mWorlds.push_back(world);
} 

void State::Pop(int amount) {
	mAmountToPop += amount;
}

void State::AddLocalEntity(Entity* entity) {
	entity->Initialize();
	mLocalEntities.push_back(entity);
}

void State::Update(const float time_delta) {
	UpdateAllEntities(time_delta);
	if(Root::get_const_instance().IsServer()) {
		for(int i = 0; i < mAmountToPop && mWorlds.size() > 0; i++) {
			mWorlds.pop_back();
		}
		mAmountToPop = 0;
	}
}

void State::Draw(sf::RenderTarget* target) {
	BOOST_FOREACH(World& world, mWorlds) {
		world.Draw(target);
	}
	BOOST_FOREACH(Entity& entity, mLocalEntities) {
		entity.Draw(target);
	}
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.Draw(target);
	}
}

void State::UpdateAllEntities(const float time_delta) {
	BOOST_FOREACH(World& world, mWorlds) {
		world.UpdateAllEntities(time_delta);
	}
	BOOST_FOREACH(Entity& entity, mLocalEntities) {
		entity.Update(time_delta);
	}
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.Update(time_delta);
	}
}

void State::AppendAllEntitiesToPacket() {
	BOOST_FOREACH(World& world, mWorlds) {
		world.AppendAllEntitiesToPacket();
	}
	BOOST_FOREACH(Entity& entity, mLocalEntities) {
		Root::get_mutable_instance().GetNetworkManagerPtr()->AppendEntityToPacket(entity);
	}
}

void State::HandleEvent(sf::Event e) {
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.HandleEvent(e);
	}
}

void State::CreateGuiSystem() {
	mGuiSystems.push_back(new GuiSystem());
}

void State::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, const sf::Uint16 world_unique_id, sf::Packet& data) {
	BOOST_FOREACH(World& world, mWorlds) {
		if(world.GetWorldUniqueId() == world_unique_id)
			world.HandleInteraction(interaction_id, client_id, data);
	}
}

World* State::GetWorld(const sf::Uint16 world_unique_id) {
	BOOST_FOREACH(World& world, mWorlds) {
		if(world.GetWorldUniqueId() == world_unique_id) {
			return &world;
		}
	}
	return NULL;
}

void State::DeleteWorldByWorldUniqueId(const sf::Uint16 world_unique_id) {
	mWorlds.erase_if(boost::bind(&World::GetWorldUniqueId, _1) == world_unique_id);
}

void State::DeleteEntitiesByClientId(const sf::Uint16 client_id) {
	BOOST_FOREACH(World& world, mWorlds) {
		world.DeleteEntitiesByClientId(client_id);
	}
	mLocalEntities.erase_if(boost::bind(&Entity::GetClientId, _1) == client_id);
}

Entity* State::GetEntityByEntityUniqueId(const sf::Uint16 entity_unique_id) {
	BOOST_FOREACH(World& world, mWorlds) {
		if (world.GetEntityByEntityUniqueId(entity_unique_id) != NULL) {
			return world.GetEntityByEntityUniqueId(entity_unique_id);
		}
	}

	return NULL;
}

void State::OnLeaveGame() {}


bool State::StatesBelowArePaused() {
	return true;
}

bool State::StatesBelowAreHidden() {
	return true;
}

void State::SendWorldSnapshots() {
	BOOST_FOREACH(World& world, mWorlds) {
		Root::get_mutable_instance().GetNetworkManagerPtr()->SendWorldInfo(world.GetWorldUniqueId(),world.GetWorldTypeId());
	}
}

bool State::IsCurrentState() {
	return Root::get_mutable_instance().GetStateManagerPtr()->IsCurrentState(this);
}

}
