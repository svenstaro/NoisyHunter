#include "GuiTextfield.hpp"

#include "Root.hpp"

namespace Engine{

GuiTextfield::GuiTextfield() {}

GuiTextfield::GuiTextfield(std::string name) {
    mName = name;
    mCursorPosition = 0;
    mHover = false;
	mIsFocused = false;
	mMultiline = false;
	SetPassword(false);

	SetDimension(Vector2D(200,20));

	SetFont(sf::Font::GetDefaultFont());
	SetFontSize(12);
	SetFontStyle(sf::Text::Regular);
	SetFontColor(sf::Color::Black);

	SetPositionType(POSITIONTYPE_SCREENPIXEL);
}

GuiTextfield::~GuiTextfield() {}

GuiTextfield* GuiTextfield::create() const {
	return new GuiTextfield();
}

void GuiTextfield::SetPassword(bool password) {
	mHideCharacters = password;
}

void GuiTextfield::Draw(sf::RenderTarget* target) {
    mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.textfield"));
	mSprite.SetPosition(mPosition.x, mPosition.y);
	mSprite.SetScale(mDimension.x, mDimension.y);
    target->Draw(mSprite);

	if (mHideCharacters)
		mText.SetString(std::string(mCaption.length(), '?')); // TODO: Change character
	else
		mText.SetString(mCaption);

	mText.SetPosition(mPosition.x + 8, round(mPosition.y + mDimension.y / 2 - mText.GetCharacterSize() / 2));
    target->Draw(mText);

    // draw cursor
    if(mIsFocused) {
		int xpos = mText.GetPosition().x + mText.GetCharacterPos(mCursorPosition).x + 1;
        int h = 15;
		int ypos = mText.GetPosition().y + mText.GetRect().Height / 2 - h / 2;
		sf::Shape cursor = sf::Shape::Rectangle(xpos, ypos, 2, h, mText.GetColor());
        target->Draw(cursor);
    }

	DrawAllAttachments(target);
}

void GuiTextfield::SetMultiline(bool multiline) {
    mMultiline = multiline;
}

void GuiTextfield::OnMouseDown() {
    int last_pos = 0;
    int last_diff = 1000;
    unsigned int i = 0;
    for(; i <= mCaption.length(); i++) {
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
        mCursorPosition = mCaption.length();
}

void GuiTextfield::OnKeyDown(sf::Key::Code key_code) {
    if(key_code == sf::Key::Back) {
		if(mCaption.length() > 0 && mCursorPosition > 0) {
			mCaption = mCaption.substr(0,mCursorPosition-1) + mCaption.substr(mCursorPosition);
			mCursorPosition -= 1;
        }
    } else if (key_code == sf::Key::Delete) {
        if (mCaption.length() > 0) {
            if (mCursorPosition < (int)mCaption.length())
                mCaption = mCaption.substr(0,mCursorPosition) + mCaption.substr(mCursorPosition+1);
        }
    } else if (key_code == sf::Key::Left) {
        if (mCursorPosition > 0)
            mCursorPosition--;
    } else if (key_code == sf::Key::Right) {
        if (mCursorPosition < (int)mCaption.length())
            mCursorPosition++;
    } else if (key_code == sf::Key::End) {
        mCursorPosition = mCaption.length();
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
       mCaption = mCaption.substr(0,mCursorPosition) + (char)unicode_char + mCaption.substr(mCursorPosition);
        mCursorPosition++;
    }
}

}
