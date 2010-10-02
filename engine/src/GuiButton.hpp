#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "GuiControl.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiButton : public GuiControl{
public:
    GuiButton();
    GuiButton(std::string name);
    ~GuiButton();

    // main callbacks
    virtual void Draw(sf::RenderTarget* target);

    void SetFont(const sf::Font& font);
    void SetFontSize(const float size);
    void SetFontStyle(unsigned long style);
    void SetFontColor(const sf::Color& color);

private:
    sf::String mString;
    TiledSprite mSprite;
};


}

#endif
