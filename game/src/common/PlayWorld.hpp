#ifndef PLAYWORLD_HPP
#define PLAYWORLD_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Logger.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Submarine.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"

#include "WorldTypeId.hpp"

#include "ParticleSystem.hpp"
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

class PlayWorld : public Engine::World {
public:
    PlayWorld();
    ~PlayWorld();
	PlayWorld* clone() const;

    // state control
    void Initialize();

	void Update(const float time_delta);

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    // input callbacks
    void OnSetNoisyMode();
    void OnSetSilentMode();

    void OnNavigateTo(const Engine::Coordinates& mouse_position);
    void OnFireTorpedo(const Engine::Coordinates& mouse_position);
	void OnFireSonarPing(const Engine::Coordinates& mouse_position);

	void TriggerFireSonarPing();
    void OnClick(Engine::MouseEventArgs args);
    void OnRightClick(Engine::MouseEventArgs args);
    void OnMouseMove(Engine::MouseEventArgs args);

	sf::Uint16 GetWorldTypeId() const;
};

#endif
