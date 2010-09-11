#include "GuiButton.hpp"

namespace Engine{

GuiButton::GuiButton() {}
GuiButton::GuiButton(std::string name) {
    mName = name;
}
GuiButton::~GuiButton() {}

// main callbacks
void GuiButton::Draw(sf::RenderTarget* target) {
    mString.SetText(mText);
    mString.SetPosition(mPosition.x + mDimension.x / 2 - mString.GetRect().GetWidth()  / 2,
                        mPosition.y + mDimension.y / 2 - mString.GetRect().GetHeight() / 2);

    sf::Color shape_color;
    if (mHover) shape_color = sf::Color(200,200,255);
    else if (mIsFocused) shape_color = sf::Color(255,255,255);
    else shape_color = sf::Color(200,200,200);

    mShape = sf::Shape::Rectangle(mPosition.x,
                                  mPosition.y,
                                  mPosition.x+mDimension.x,
                                  mPosition.y+mDimension.y,
                                  shape_color);



    target->Draw(mShape);
    target->Draw(mString);
}

// event callbacks
void GuiButton::OnClick() {

}

}
