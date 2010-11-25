#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include <SFML/System/Vector2.hpp>

#include "LogManager.hpp"
#include "Submarine.hpp"
#include "SonarPing.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"
#include "World.hpp"

class MainWorld : public Engine::World {
public:
    MainWorld();
    ~MainWorld();

    void Initialize();

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
