#include "GuiButton.hpp"

#include "Root.hpp"

namespace Engine{

GuiButton::GuiButton() {}
GuiButton::GuiButton(std::string name) {
    mName = name;
    mHover = false;
    mIsFocused = false;
    SetFontSize(16);
    SetFontStyle(sf::Text::Bold);
    SetFontColor(sf::Color(0,0,0));
}

GuiButton::~GuiButton() {}

GuiButton* GuiButton::clone() const {
	return new GuiButton();
}

void GuiButton::SetFont(const sf::Font& font) {
    mText.SetFont(font);
}

void GuiButton::SetFontSize(const float size) {
    mText.SetCharacterSize(size);
}

void GuiButton::SetFontStyle(unsigned long style) {
    mText.SetStyle(style);
}

void GuiButton::SetFontColor(const sf::Color& color) {
    mText.SetColor(color);
}

// main callbacks
void GuiButton::Draw(sf::RenderTarget* target) {
    mText.SetString(mString);
    mText.SetPosition(mPosition.x + mDimension.x / 2 - mText.GetRect().Width  / 2,
                        mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2);

    if (mHover)
        mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.button_hover"));
    else
        mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.button"));

    if (mIsFocused)
        mText.SetColor(sf::Color(255,0,0));
    else
        mText.SetColor(sf::Color(0,0,0));

    /*sf::Color shape_color;
    if (mHover) shape_color = sf::Color(200,200,255);
    else if (mIsFocused) shape_color = sf::Color(255,255,255);
    else shape_color = sf::Color(200,200,200);

    mShape = sf::Shape::Rectangle(mPosition.x,
        e                          mPosition.y,
                                  mPosition.x+mDimension.x,
                                  mPosition.y+mDimension.y,
                                  shape_color);
*/
    mSprite.SetPosition(mPosition.x, mPosition.y);
	mSprite.SetScale(mDimension.x, mDimension.y);


    target->Draw(mSprite);
    target->Draw(mText);
}

}
