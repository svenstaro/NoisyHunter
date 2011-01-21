#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <string>

#include "Logger.hpp"
#include "State.hpp"
#include "InputManager.hpp"
#include "PlayState.hpp"

#include "Radar.hpp"

//#include "GuiTextfield.hpp"
#include "GuiButton.hpp"
//#include "GuiCheckbox.hpp"
//#include "GuiProgressbar.hpp"
#include "GuiGrid.hpp"

class MenuState : public Engine::State {
public:
	MenuState();
	~MenuState();

	// state control
	void Initialize();
	void Shutdown();

	void Update(float time_delta);

	// input callbacks
	void OnPressEscape();

	// gui callbacks
	void PlayButton_OnClick(const sf::Uint16 mouse_button);
	void StartServerButton_OnClick(const sf::Uint16 mouse_button);
	void OptionsButton_OnClick(const sf::Uint16 mouse_button);
	void QuitButton_OnClick(const sf::Uint16 mouse_button);
private:
};

#endif
