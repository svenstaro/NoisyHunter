#include "State.hpp"

namespace Engine{

    void State::Update(const float time_delta){
        UpdateAllEntities(time_delta);
    }

    void State::UpdateAllEntities(const float time_delta){
        BOOST_FOREACH(Entity& entity, mEntities){
            entity.Update(time_delta);
        }

        if (mEntityListNeedsSorting) {
            mEntities.sort();
            mEntityListNeedsSorting = false;
        }
    }


    void State::Draw(const sf::RenderTarget& target) const {
        BOOST_FOREACH(Entity& entity, mEntities){
            entity.Draw(target);
        }
    }


    void State::AddEntity(const Entity& entity){
        mEntities.push_back(&entity);
        mEntityListNeedsSorting = true;
    }




}
