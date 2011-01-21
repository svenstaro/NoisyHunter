#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Logger.hpp"
#include "State.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Submarine.hpp"
#include "WorldPolygon.hpp"
#include "Interaction.hpp"

#include "GuiTextfield.hpp"
#include "GuiButton.hpp"
#include "GuiCheckbox.hpp"
#include "GuiProgressbar.hpp"
#include "GuiGrid.hpp"

#include "ParticleSystem.hpp"
#include "ParticleEmitter.hpp"
#include "Particle.hpp"

#include "PauseState.hpp"

class PlayState : public Engine::State {
public:
    PlayState();
    ~PlayState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);

	void OnScreenshot();

    void OnPauseGame();
    // network callbacks
    void OnClientConnected(const sf::Uint16 client_id);
    
    // gui callbacks
	void MenuButton_OnClick(const sf::Uint16 mouse_button);

private:
	Engine::Entity* mCursorPartSys; // I know this is ugly, we need a better system for this!
};

#endif
