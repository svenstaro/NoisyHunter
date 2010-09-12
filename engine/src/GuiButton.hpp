#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

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

    // event callbacks
    void OnClick();
private:
    sf::String mString;
    //sf::Shape mShape;
    TiledSprite mSprite;
};


}

#endif
