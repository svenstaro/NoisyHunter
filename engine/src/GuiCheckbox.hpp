#ifndef GUICHECKBOX_HPP
#define GUICHECKBOX_HPP

#include <SFML/Graphics.hpp>
#include "GuiControl.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiCheckbox : public GuiControl{
public:
    GuiCheckbox();

    GuiCheckbox(std::string name);

    ~GuiCheckbox();

	GuiCheckbox* clone() const;

    // main callbacks
	void Draw(sf::RenderTarget* target, Vector2D offset = Vector2D(0,0));
    bool IsAtPoint(const Vector2D point);

    void SetChecked(const bool is_checked);
    bool Checked();
    void ToggleChecked();

    void SetFont(const sf::Font& font);
    void SetFontSize(const float size);
    void SetFontStyle(unsigned long style);
    void SetFontColor(const sf::Color& color);

    // event callbacks
	void OnMouseUp();
    void OnKeyDown(sf::Key::Code key_code);
private:
    sf::Text mText;
    sf::Sprite mSprite;
    bool mIsChecked;
};


}

#endif
