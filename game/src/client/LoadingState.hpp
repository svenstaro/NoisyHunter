#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "State.hpp"
#include "InputManager.hpp"
#include "GuiSystem.hpp"
#include "GuiButton.hpp"
#include "GuiProgressbar.hpp"
#include "GuiCheckbox.hpp"
#include "GuiTextfield.hpp"
#include "PlayState.hpp"

class LoadingState : public Engine::State{
public:
    LoadingState();
    ~LoadingState();

    // state control
    void Initialize();
    void Shutdown();

	void Update(float time_delta);
    //void Draw(sf::RenderTarget* target);

    void OnCancel();
    void OnClick(Engine::MouseEventArgs args);
    void OnAnyKeyPressed();
private:
    Engine::GuiSystem mGuiSystem;
};

#endif
