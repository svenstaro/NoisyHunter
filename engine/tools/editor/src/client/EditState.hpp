#ifndef EDITSTATE_HPP
#define EDITSTATE_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "Logger.hpp"
#include "State.hpp"
#include "Entity.hpp"
#include "InputManager.hpp"
#include "Interaction.hpp"

#include "GuiTextfield.hpp"
#include "GuiButton.hpp"
#include "GuiCheckbox.hpp"
#include "GuiProgressbar.hpp"
#include "GuiGrid.hpp"

#include "Grid.hpp"

class EditState : public Engine::State {
public:
	EditState();
	~EditState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);

	// network callbacks
    void OnClientConnected(const sf::Uint16 client_id);
    
    // gui callbacks
	//void MenuButton_OnClick(const sf::Uint16 mouse_button);
};

#endif
