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
    virtual void Draw(sf::RenderTarget* target);

private:
    TiledSprite mSprite;
};


}

#endif
