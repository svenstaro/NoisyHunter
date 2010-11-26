#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include <SFML/System/Vector2.hpp>

#include "LogManager.hpp"
#include "Submarine.hpp"
#include "SonarPing.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"
#include "World.hpp"
#include "WorldTypeId.hpp"

class MainWorld : public Engine::World {
public:
    MainWorld();
    ~MainWorld();
	MainWorld* clone() const;

    void Initialize();

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);
	sf::Uint16 GetWorldTypeId() const;

private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
