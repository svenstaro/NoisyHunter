#include "GuiCheckbox.hpp"

#include "Root.hpp"

namespace Engine{

GuiCheckbox::GuiCheckbox() {}

GuiCheckbox::GuiCheckbox(std::string name) {
    mIsChecked = false;
    mName = name;
    mHover = false;
    mIsFocused = false;
    SetFontSize(12);
    SetFontStyle(sf::String::Bold);
    SetFontColor(sf::Color(0,0,0));
}

GuiCheckbox::~GuiCheckbox() {}

GuiCheckbox* GuiCheckbox::clone() const {
	return new GuiCheckbox();
}

bool GuiCheckbox::IsAtPoint(const Vector2D point) {
    return (point.x >= mPosition.x and
            point.y >= mPosition.y and
            point.x <= mPosition.x + 20 + mString.GetRect().GetWidth() and
            point.y <= mPosition.y + 16);
}

void GuiCheckbox::SetChecked(const bool is_checked) {
    mIsChecked = is_checked;
}

bool GuiCheckbox::Checked() {
    return mIsChecked;
}

void GuiCheckbox::ToggleChecked() {
    mIsChecked = !mIsChecked;
}

void GuiCheckbox::SetFont(const sf::Font& font) {
    mString.SetFont(font);
}

void GuiCheckbox::SetFontSize(const float size) {
    mString.SetSize(size);
}

void GuiCheckbox::SetFontStyle(unsigned long style) {
    mString.SetStyle(style);
}

void GuiCheckbox::SetFontColor(const sf::Color& color) {
    mString.SetColor(color);
}

// main callbacks
void GuiCheckbox::Draw(sf::RenderTarget* target) {
    mString.SetText(mText);
    mString.SetPosition(mPosition.x + 20,mPosition.y);

    if (mIsChecked)  mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.checkbox_checked"));
    else if (mHover) mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.checkbox_hover"));
    else             mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.checkbox"));

    mSprite.SetPosition(mPosition.x, mPosition.y);
    mSprite.Resize(16,16);

    target->Draw(mSprite);
    target->Draw(mString);
}

// event callbacks
void GuiCheckbox::OnClick() {
    ToggleChecked();
}

void GuiCheckbox::OnKeyDown(sf::Key::Code key_code) {
    if (key_code == sf::Key::Space or key_code == sf::Key::Return) {
        ToggleChecked();
    }
}

}
