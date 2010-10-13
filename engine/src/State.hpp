#ifndef STATE_HPP
#define STATE_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signals2.hpp>

#include <SFML/Graphics.hpp>

#include "GuiSystem.hpp"
#include "Entity.hpp"

namespace Engine {

class Root;

class State {
public:
    State();
    virtual ~State() = 0;

    virtual void Initialize() = 0;

    virtual void Update(const float time_delta);
    void UpdateAllEntities(const float time_delta); // TODO: This should 
	// probably be private if it is never called from the outside.
    void AppendAllEntitiesToPacket();

    // Draws all entities to render target.
    void HandleEvent(sf::Event e);
    void Draw(sf::RenderTarget* const target);

    void AddEntity(Entity* entity);
    void CreateGuiSystem();
	void HandleEntityInfo(sf::Packet packet);
    Entity* GetEntityByUniqueId(const sf::Uint16 unique_id);

protected:
    //Root* mRoot;

    // Entity list
    boost::ptr_vector<Entity> mEntities;

    // Gui Systems
    boost::ptr_vector<GuiSystem> mGuiSystems;

private:
    // Saves if there are new Entities, so the list has to be sorted for correct order while drawing.
    bool mEntityListNeedsSorting;
};

}

#endif
