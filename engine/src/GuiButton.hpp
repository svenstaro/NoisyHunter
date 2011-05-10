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

	GuiButton* create() const;

    // main callbacks
	virtual void Draw(sf::RenderTarget* target);

	// Signals & slots
	virtual void BindOnClick(const boost::signals2::signal<void (const sf::Uint16 mouse_button)>::slot_type& slot);
	virtual void TriggerOnClick(const sf::Uint16 mouse_button);

	// Internal callback, called from input manager
	void OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);

	void SetIcon(sf::Sprite& icon);
	void SetIconSize(float size = DefaultIconSize);
	//float GetDefaultIconSize();
	//float GetAutoscaleIconSize();
	static const float DefaultIconSize;
	static const float AutoscaleIconSize;

private:
	// Click signal
	boost::signals2::signal<void (const sf::Uint16 mouse_button)> mOnClickSignal;

	TiledSprite mSprite;
	sf::Sprite mIconSprite;
	float mIconSize;

};


}

#endif
