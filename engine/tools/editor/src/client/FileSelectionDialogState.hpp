#ifndef FILESELECTIONDIALOGSTATE_HPP
#define FILESELECTIONDIALOGSTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "GuiButton.hpp"
#include "GuiTextfield.hpp"
#include "GuiGrid.hpp"

class FileSelectionDialogState : public Engine::State {
public:
	FileSelectionDialogState();
	~FileSelectionDialogState();

	void Initialize();
	void Shutdown();

	void Update(float time_delta);
	void Draw(sf::RenderTarget* target);

	bool StatesBelowArePaused();
	bool StatesBelowAreHidden();

	void OkButton_OnClick(const sf::Uint16 mouse_button);

	void ExitButton_OnClick(const sf::Uint16 mouse_button);
	void OnPressEscape();

private:
	sf::Shape mBackgroundShape;
};


#endif
