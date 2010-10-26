#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "LogManager.hpp"
#include "State.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Crosshair.hpp"
#include "Submarine.hpp"
#include "Interaction.hpp"

#include "GuiTextfield.hpp"
#include "GuiButton.hpp"
#include "GuiCheckbox.hpp"
#include "GuiProgressbar.hpp"

#include "ParticleSystem.hpp"
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

class PlayState : public Engine::State {
public:
    PlayState();
    ~PlayState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);

    // input callbacks
    void OnSetNoisyMode();
    void OnSetSilentMode();

    void OnNavigateTo(const Engine::Coordinates& mouse_position);
    void OnFireTorpedo(const Engine::Coordinates& mouse_position);

    void OnLeaveGame();
    void OnClick(Engine::MouseEventArgs args);
    void OnRightClick(Engine::MouseEventArgs args);
    void OnMouseMove(Engine::MouseEventArgs args);
    
    // network callbacks
    void OnClientConnected(const std::string& client_name);
    
    // gui callbacks
	void ExitButton_OnClick(const sf::Uint16 mouse_button);

private:
    Crosshair* mCrosshair;
    Submarine* mPlayerSubmarine;
};

#endif
