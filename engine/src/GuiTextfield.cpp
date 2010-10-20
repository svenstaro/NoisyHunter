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
        mText.SetString(std::string(mString.length(), '?'));
        mText.SetFont(sf::Font::GetDefaultFont());
    } else {
        mText.SetString(mString);
        mText.SetFont(*mFont);
    }

    mText.SetPosition(mPosition.x+3, mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2);
    target->Draw(mText);

    // draw cursor
    if(mIsFocused) {
        int xpos = mText.GetPosition().x + mText.GetCharacterPos(mCursorPosition).x + 1;
        int h = 15;
        int ypos = mText.GetPosition().y + mText.GetRect().Height / 2 - h / 2;
        sf::Shape cursor = sf::Shape::Rectangle(xpos, ypos, xpos+2, ypos+h, mText.GetColor());
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
    mText.SetFont(font);
    mFont = &font;
}

void GuiTextfield::SetFontSize(const float size) {
    mText.SetCharacterSize(size);
}

void GuiTextfield::SetFontStyle(unsigned long style) {
    mText.SetStyle(style);
}

void GuiTextfield::SetFontColor(const sf::Color& color) {
    mText.SetColor(color);
}

void GuiTextfield::OnClick() {
    int last_pos = 0;
    int last_diff = 1000;
    unsigned int i = 0;
    for(; i <= mString.length(); i++) {
        int pos = mText.GetPosition().x + mText.GetCharacterPos(i).x;
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
        mCursorPosition = mString.length();
}

void GuiTextfield::OnKeyDown(sf::Key::Code key_code) {
    if(key_code == sf::Key::Back) {
        if(mString.length() > 0) {
            mString = mString.substr(0,mCursorPosition-1) + mString.substr(mCursorPosition);
            if (mCursorPosition > 0)
                mCursorPosition -= 1;
        }
    } else if (key_code == sf::Key::Delete) {
        if (mString.length() > 0) {
            if (mCursorPosition < (int)mString.length())
                mString = mString.substr(0,mCursorPosition) + mString.substr(mCursorPosition+1);
        }
    } else if (key_code == sf::Key::Left) {
        if (mCursorPosition > 0)
            mCursorPosition--;
    } else if (key_code == sf::Key::Right) {
        if (mCursorPosition < (int)mString.length())
            mCursorPosition++;
    } else if (key_code == sf::Key::End) {
        mCursorPosition = mString.length();
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
       mString = mString.substr(0,mCursorPosition) + (char)unicode_char + mString.substr(mCursorPosition);
        mCursorPosition++;
    }
}

}
