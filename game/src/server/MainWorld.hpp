#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include <SFML/System/Vector2.hpp>

#include "LogManager.hpp"
#include "State.hpp"
#include "Submarine.hpp"
#include "SonarPing.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"

class MainWorld : public Engine::World{
public:
    MainWorld();
    ~MainWorld();

    // state control
    void Initialize();

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    void Update(float time_delta);
	void OnClientConnected(sf::Uint16 client_id);
private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
