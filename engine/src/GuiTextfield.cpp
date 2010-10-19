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
    SetDimension(Vector2D(200,20));
    mMultiline = false;
    SetPassword(true);

    SetFont(sf::Font::GetDefaultFont());
}

GuiTextfield::~GuiTextfield() {}

GuiTextfield* GuiTextfield::clone() const {
	return new GuiTextfield();
}

void GuiTextfield::Draw(sf::RenderTarget* target) {
    mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.textfield"));
    mSprite.SetPosition(mPosition.x, mPosition.y);
    mSprite.Resize(mDimension.x, mDimension.y);
    target->Draw(mSprite);

    if (mHideCharacters) {
        mString.SetText(std::string(mText.length(), '?'));
        mString.SetFont(sf::Font::GetDefaultFont());
    } else {
        mString.SetText(mText);
        mString.SetFont(*mFont);
    }

    mString.SetPosition(mPosition.x+3, mPosition.y + mDimension.y / 2 - mString.GetRect().GetHeight() / 2);
    target->Draw(mString);

    // draw cursor
    if(mIsFocused) {
        int xpos = mString.GetPosition().x + mString.GetCharacterPos(mCursorPosition).x + 1;
        int h = 15;
        int ypos = mString.GetPosition().y + mString.GetRect().GetHeight() / 2 - h / 2;
        sf::Shape cursor = sf::Shape::Rectangle(xpos, ypos, xpos+2, ypos+h, mString.GetColor());
        target->Draw(cursor);
    }
}

void GuiTextfield::SetMultiline(bool multiline) {
    mMultiline = multiline;
}

void GuiTextfield::SetPassword(bool password) {
    mHideCharacters = password;
}

void GuiTextfield::SetFont(const sf::Font& font) {
    mString.SetFont(font);
    mFont = &font;
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
    int last_pos = 0;
    int last_diff = 1000;
    unsigned int i = 0;
    for(; i <= mText.length(); i++) {
        int pos = mString.GetPosition().x + mString.GetCharacterPos(i).x;
        int diff = Root::get_mutable_instance().GetInputManagerPtr()->GetMousePosition().x - pos;

        if(abs(diff) > abs(last_diff)) {
            mCursorPosition = i - 1; // last one was the closest
            break;
        } else {
            last_diff = diff;
            last_pos = pos;
        }
    }

    if (mCursorPosition != (int)i-1)
        mCursorPosition = mText.length();
}

void GuiTextfield::OnKeyDown(sf::Key::Code key_code) {
    if(key_code == sf::Key::Back) {
        if(mText.length() > 0) {
            mText = mText.substr(0,mCursorPosition-1) + mText.substr(mCursorPosition);
            if (mCursorPosition > 0)
                mCursorPosition -= 1;
        }
    } else if (key_code == sf::Key::Delete) {
        if (mText.length() > 0) {
            if (mCursorPosition < (int)mText.length())
                mText = mText.substr(0,mCursorPosition) + mText.substr(mCursorPosition+1);
        }
    } else if (key_code == sf::Key::Left) {
        if (mCursorPosition > 0)
            mCursorPosition--;
    } else if (key_code == sf::Key::Right) {
        if (mCursorPosition < (int)mText.length())
            mCursorPosition++;
    } else if (key_code == sf::Key::End) {
        mCursorPosition = mText.length();
    } else if (key_code == sf::Key::Home) {
        mCursorPosition = 0;
    }
}

void GuiTextfield::OnType(sf::Uint32 unicode_char) {
    // the following IF statement saves us from unwanted and not interpreted escape
    // sequences like "\b" which would be added when hitting <Backspace>
    if(unicode_char != 8 and   // backspace
       unicode_char != 9 and   // tab
       unicode_char != 13 and  // return
       unicode_char != 127) {   // delete
       mText = mText.substr(0,mCursorPosition) + (char)unicode_char + mText.substr(mCursorPosition);
        mCursorPosition++;
    }
}

}
