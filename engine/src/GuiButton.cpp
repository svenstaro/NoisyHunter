#include "GuiButton.hpp"

#include "Root.hpp"

namespace Engine {

const float GuiButton::DefaultIconSize = -1;
const float GuiButton::AutoscaleIconSize = -2;

GuiButton::GuiButton() {}

GuiButton::GuiButton(std::string name) {
    mName = name;
    mHover = false;
    mIsFocused = false;

	SetFont(sf::Font::GetDefaultFont());
	SetFontSize(12);
	SetFontStyle(sf::Text::Regular);
	SetFontColor(sf::Color::Black);

	SetPositionType(POSITIONTYPE_SCREENPIXEL);
}

GuiButton::~GuiButton() {}

GuiButton* GuiButton::create() const {
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

	mSprite.SetPosition(mPosition.x, mPosition.y);
	mSprite.SetScale(mDimension.x, mDimension.y);

    target->Draw(mSprite);
    target->Draw(mText);

	if(mIconSprite.GetImage() != NULL) {
		float image_factor = 0.4f;

		const sf::Image* icon_image = mIconSprite.GetImage();

		if(mIconSize == DefaultIconSize) {
			mIconSprite.SetScale(1.f, 1.f);
		} else if(mIconSize == AutoscaleIconSize){
			// scale to maximum
			float scale = std::min(mDimension.x / icon_image->GetWidth() * image_factor, mDimension.y / icon_image->GetHeight() * image_factor);
			mIconSprite.SetScale(scale, scale);
		} else {
			// use mIconSize as scale factor
			mIconSprite.SetScale(mIconSize, mIconSize);
		}

		// position icon left of text
		float margin = 5.f;
		if(mCaption == "") margin = - icon_image->GetWidth() * mIconSprite.GetScale().x; // half sized margin if no text => centered icon
		mIconSprite.SetPosition(mPosition.x + mDimension.x / 2 - mText.GetRect().Width / 2 - margin - icon_image->GetWidth() * mIconSprite.GetScale().x,
						 mPosition.y + mDimension.y / 2 - icon_image->GetHeight() * mIconSprite.GetScale().y / 2);
		target->Draw(mIconSprite);
	}

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

void GuiButton::SetIcon(sf::Sprite& icon) {
	mIconSprite = icon;
}

void GuiButton::SetIconSize(float size) {
	mIconSize = size;
}

/*float GuiButton::GetDefaultIconSize() {
	return DefaultIconSize;
}

float GuiButton::GetAutoscaleIconSize() {
	return AutoscaleIconSize;
}*/

}
