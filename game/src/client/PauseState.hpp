#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "GuiButton.hpp"

class PauseState : public Engine::State {
public:
	PauseState();
	~PauseState();

	void Initialize();
	void Shutdown();

	void Update(float time_delta);
	void Draw(sf::RenderTarget* target);

	bool StatesBelowArePaused();
	bool StatesBelowAreHidden();

	void ResumeButton_OnClick(const sf::Uint16 mouse_button);
	void ExitButton_OnClick(const sf::Uint16 mouse_button);
	void OnPressEscape();

private:
	sf::Shape mBackgroundShape;
};


#endif
