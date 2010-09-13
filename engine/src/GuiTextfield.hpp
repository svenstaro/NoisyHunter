#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "GuiControl.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiTextfield : public GuiControl{
public:
    GuiTextfield();
    GuiTextfield(std::string name);
    ~GuiTextfield();

    // main callbacks
    void Draw(sf::RenderTarget* target);

    void SetFont(const sf::Font& font);
    void SetFontSize(const float size);
    void SetFontStyle(unsigned long style);
    void SetFontColor(const sf::Color& color);

    // event callbacks
    void OnClick();
    void OnKeyDown(sf::Key::Code key_code);
    void OnType(sf::Uint32 unicode_char);
private:
    sf::String mString;
    TiledSprite mSprite;

    int mCursorPosition;
};

}

#endif
