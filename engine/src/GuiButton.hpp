#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "GuiLabel.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiButton : public GuiLabel{
public:
    GuiButton();

    GuiButton(std::string name);

    ~GuiButton();

	GuiButton* clone() const;

    // main callbacks
	virtual void Draw(sf::RenderTarget* target, Vector2D offset = Vector2D(0,0));

	// Signals & slots
	virtual void BindOnClick(const boost::signals2::signal<void (const sf::Uint16 mouse_button)>::slot_type& slot);
	virtual void TriggerOnClick(const sf::Uint16 mouse_button);

	// Internal callback, called from input manager
	void OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);

private:
	// Click signal
	boost::signals2::signal<void (const sf::Uint16 mouse_button)> mOnClickSignal;

	TiledSprite mSprite;
};


}

#endif
