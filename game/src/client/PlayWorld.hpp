#ifndef PLAYWORLD_HPP
#define PLAYWORLD_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "LogManager.hpp"
#include "State.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Submarine.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"

#include "ParticleSystem.hpp"
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

#include "PauseState.hpp"

class PlayWorld : public Engine::World {
public:
    PlayWorld();
    ~PlayWorld();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);

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
    
};

#endif
