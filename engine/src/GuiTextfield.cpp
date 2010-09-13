#include "GuiTextfield.hpp"

#include "Root.hpp"

namespace Engine{

GuiTextfield::GuiTextfield() {}
GuiTextfield::GuiTextfield(std::string name) {
    mName = name;
    mCursorPosition = 0;
    mHover = false;
    mIsFocused = false;
    SetFontSize(16);
    SetFontColor(sf::Color(0,0,0));
}
GuiTextfield::~GuiTextfield() {}

void GuiTextfield::Draw(sf::RenderTarget* target) {
    mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.textfield"));
    mSprite.SetPosition(mPosition.x, mPosition.y);
    mSprite.Resize(mDimension.x, mDimension.y);
    target->Draw(mSprite);

    mString.SetText(mText + (mIsFocused?"|":"") );
    mString.SetPosition(mPosition.x, mPosition.y);
    target->Draw(mString);
}
void GuiTextfield::SetFont(const sf::Font& font) {
    mString.SetFont(font);
}
void GuiTextfield::SetFontSize(const float size) {
    mString.SetSize(size);
}
void GuiTextfield::SetFontStyle(unsigned long style) {
    mString.SetStyle(style);
}
void GuiTextfield::SetFontColor(const sf::Color& color) {
    mString.SetColor(color);
}
void GuiTextfield::OnClick() {

}
void GuiTextfield::OnKeyDown(sf::Key::Code key_code) {

    if (key_code == sf::Key::Back){
        if (mText.length() > 0){
            mText.erase(mText.capacity() - 1, 1);
            mText.resize(mText.capacity() - 1);
        }
    }

}
void GuiTextfield::OnType(sf::Uint32 unicode_char){
    mText += (char)unicode_char;
}

}
