#include "State.hpp"
#include "Root.hpp"

#include <boost/foreach.hpp>
#include <SFML/Graphics.hpp>

namespace Engine{

    State::State() {}
    State::~State() {}

    void State::Update(const float time_delta){
        UpdateAllEntities(time_delta);
    }

    void State::UpdateAllEntities(const float time_delta){
        BOOST_FOREACH(Entity& entity, mEntities){
            entity.Update(time_delta);
        }

        if (mEntityListNeedsSorting) {
            //mEntities.sort();
            mEntityListNeedsSorting = false;
        }


        BOOST_FOREACH(GuiSystem& system, mGuiSystems){
            system.Update(time_delta);
        }

    }
	
	void State::SendAllEntities() {
		BOOST_FOREACH(Entity& entity, mEntities) {
			Root::get_mutable_instance().GetNetworkManagerPtr()->AddEntity(entity);
		}
	}

    void State::Draw(sf::RenderTarget* target) {
        BOOST_FOREACH(Entity& entity, mEntities){
            entity.Draw(target);
        }

        BOOST_FOREACH(GuiSystem& system, mGuiSystems){
            system.Draw(target);
        }
    }

    void State::HandleEvent(sf::Event e) {
        BOOST_FOREACH(GuiSystem& system, mGuiSystems){
            system.HandleEvent(e);
        }
    }

    void State::AddEntity(Entity* entity){
        mEntities.push_back( entity );
        mEntityListNeedsSorting = true;
    }

    void State::CreateGuiSystem() {
        mGuiSystems.push_back(new GuiSystem());
    }



}
