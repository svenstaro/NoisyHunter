#ifndef EDITWORLD_HPP
#define EDITWORLD_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Logger.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Interaction.hpp"

#include "WorldTypeId.hpp"

#include "Tile.hpp"

class EditWorld : public Engine::World {
public:
	EditWorld();
	~EditWorld();
	EditWorld* clone() const;

    // state control
    void Initialize();

	void Update(const float time_delta);

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    void OnClick(Engine::MouseEventArgs args);
    void OnRightClick(Engine::MouseEventArgs args);
    void OnMouseMove(Engine::MouseEventArgs args);

	sf::Uint16 GetWorldTypeId() const;
};

#endif
