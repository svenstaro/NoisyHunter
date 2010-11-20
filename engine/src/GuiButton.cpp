#include "GuiButton.hpp"

#include "Root.hpp"

namespace Engine {

GuiButton::GuiButton() {}

GuiButton::GuiButton(std::string name) {
    mName = name;
    mHover = false;
    mIsFocused = false;

	SetFont(sf::Font::GetDefaultFont());
	SetFontSize(12);
	SetFontStyle(sf::Text::Regular);
	SetFontColor(sf::Color::Black);
}

GuiButton::~GuiButton() {}

GuiButton* GuiButton::clone() const {
	return new GuiButton();
}

// main callbacks
void GuiButton::Draw(sf::RenderTarget* target) {
	mText.SetString(mCaption);
	mText.SetPosition(int(mPosition.x + mDimension.x / 2 - mText.GetRect().Width  / 2),	// convert to int to prevent blurry font due to half pixel coordinates
					  int(mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2));

    if(mHover)
        mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.button_hover"));
	else if(mIsFocused)
		mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.button_focus"));
	else
        mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.button"));

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

	DrawAllAttachments(target);
}

// Signals & slots

void GuiButton::BindOnClick(const boost::signals2::signal<void (const sf::Uint16)>::slot_type& slot) {
	mOnClickSignal.connect(slot);
}

void GuiButton::TriggerOnClick(const sf::Uint16 mouse_button) {
	mOnClickSignal(mouse_button);
}

// Internal callback, called from input manager
void GuiButton::OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	TriggerOnClick(mouse_button);
}

}
