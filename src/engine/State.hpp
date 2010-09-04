#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "Root.hpp"
#include "Entity.hpp"

namespace Engine{

class State{
public:
    State();
    virtual ~State() = 0;


    virtual void Update(const float time_delta);
    void UpdateAllEntities(const float time_delta);

    // Draws all entities to render target.
    void Draw(sf::RenderTarget* const target) const;

    void AddEntity(Entity* entity);

protected:
    Root* mRoot;

private:
    // Entity list
    boost::ptr_vector<Entity> mEntities;
    // Saves if there are new Entities, so the list has to be sorted for correct order while drawing.
    bool mEntityListNeedsSorting;


};

}

#endif
