#include "GuiControl.hpp"

namespace Engine {

GuiControl::GuiControl(const sf::Uint16 unique_id, 
					   const std::string& name) {
	mUniqueId = unique_id;
    mName = name;
    SetFocus(false);
    SetHover(false);
}

GuiControl::~GuiControl() {}

void GuiControl::Update(const float time_delta) {
	// TODO: Do stuff
}

void GuiControl::Draw(sf::RenderTarget* target) {
    sf::Color col(255,128,0);
    if (mHover)
        col = sf::Color(255,255,0);
    if (mIsFocused)
        col = sf::Color(255,255,255);

    sf::Shape s = sf::Shape::Rectangle(mPosition.x,
                                       mPosition.y,
                                       mPosition.x+mDimension.x,
                                       mPosition.y+mDimension.y,
                                       col);
    target->Draw(s);
}

void GuiControl::OnType(sf::Uint32 unicode_char) {
	// TODO: Do stuff
}

void GuiControl::OnClick() {
    std::cout << "Clicked on element" << std::endl;
}

void GuiControl::OnRightClick() {
	// TODO: Do stuff
}

void GuiControl::OnKeyDown(sf::Key::Code key_code) {
    if (key_code == sf::Key::Return){
        OnClick();
    }
}

sf::Uint16 GuiControl::GetEntityId() const {
	return 60000;
}

bool GuiControl::IsAtPoint(const Vector2D point) {
    return (point.x >= mPosition.x and
            point.y >= mPosition.y and
            point.x <= mPosition.x + mDimension.x and
            point.y <= mPosition.y + mDimension.y);
}

void GuiControl::SetFocus(bool is_focused) {
    mIsFocused = is_focused;
}

bool GuiControl::HasFocus() const {
    return mIsFocused;
}

void GuiControl::SetHover(bool hover) {
    mHover = hover;
}

Entity::PositionType GuiControl::GetPositionType() const {
    return Entity::POSITIONTYPE_SCREEN;
}

void GuiControl::SetPosition(const Vector2D position) {
    mPosition = position;
}

const Vector2D GuiControl::GetPosition() const {
    return mPosition;
}

void GuiControl::SetDimension(const Vector2D dimension) {
    mDimension = dimension;
}

const Vector2D GuiControl::GetDimension() const {
    return mDimension;
}

void GuiControl::SetText(std::string text) {
    mText = text;
}

const std::string GuiControl::GetText() const {
    return mText;
}

const std::string GuiControl::GetName() const {
    return mName;
}

}
