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

void State::Update(const float time_delta) {
	UpdateAllEntities(time_delta);
	for(int i = 0; i < mAmountToPop && mWorlds.size() > 0; i++) {
		mWorlds.pop_back();
	}
	mAmountToPop = 0;
}

void State::UpdateAllEntities(const float time_delta) {
	BOOST_FOREACH(GuiSystem& system, mGuiSystems) {
		system.Update(time_delta);
	}
	BOOST_FOREACH(World& world, mWorlds) {
		world.UpdateAllEntities(time_delta);
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

World* State::GetWorld(const sf::Uint16 world_unique_id) {
	BOOST_FOREACH(World& world, mWorlds) {
		if(world.GetWorldUniqueId() == world_unique_id) {
			return &world;
		}
	}
	return NULL;
}

void State::DeleteWorldByEntityUniqueId(const sf::Uint16 world_unique_id) {
	mWorlds.erase_if(boost::bind(&World::GetWorldUniqueId, _1) == world_unique_id);
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
