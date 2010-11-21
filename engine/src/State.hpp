#ifndef STATE_HPP
#define STATE_HPP

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/signals2.hpp>

#include <SFML/Graphics.hpp>

#include "GuiSystem.hpp"
#include "Entity.hpp"
#include "World.hpp"

namespace Engine {

class Root;

class State {
public:
    State();
    virtual ~State() = 0;

    virtual void Initialize() = 0;
	virtual void Shutdown();

	void AddWorld(World* world);
	void Pop(int amount);

    virtual void Update(const float time_delta);
    void UpdateAllEntities(const float time_delta); // TODO: This should 
	// probably be private if it is never called from the outside.
    void AppendAllEntitiesToPacket();

    // Draws all entities to render target.
    void HandleEvent(sf::Event e);
    void Draw(sf::RenderTarget* const target);

    void CreateGuiSystem();

	World* GetWorld(const sf::Uint16 entity_unique_id);

	// Server-side handling of Interactions
	virtual void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    Entity* GetEntityByEntityUniqueId(const sf::Uint16 entity_unique_id);
	void DeleteWorldByEntityUniqueId(const sf::Uint16 entity_unique_id); 

	virtual void OnLeaveGame();
	void DeleteEntitiesByClientId(const sf::Uint16 client_id);
	void DeleteEntityByEntityUniqueId(const sf::Uint16 entity_unique_id);

	virtual bool StatesBelowArePaused();
	virtual bool StatesBelowAreHidden();

	bool IsCurrentState();

protected:
	// Gui Systems
    boost::ptr_vector<GuiSystem> mGuiSystems;
	boost::ptr_vector<World> mWorlds;

private:
	int mAmountToPop;
};

}

#endif
