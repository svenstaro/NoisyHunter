#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "State.hpp"
#include "InputManager.hpp"
#include "GuiSystem.hpp"
#include "GuiButton.hpp"
#include "GuiProgressbar.hpp"
#include "GuiCheckbox.hpp"
#include "GuiTextfield.hpp"
#include "MenuState.hpp"

class IntroState : public Engine::State{
public:
	IntroState();
	~IntroState();

    // state control
    void Initialize();
    void Shutdown();

	void Update(float time_delta);
    //void Draw(sf::RenderTarget* target);

    void OnCancel();
    void OnClick(Engine::MouseEventArgs args);
    void OnAnyKeyPressed();

	void SetShowMenu(bool show_menu);
private:
    Engine::GuiSystem mGuiSystem;
	bool mFinishedLoading;
	bool mShowMenu;
};

#endif
