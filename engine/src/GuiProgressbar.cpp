#include "GuiProgressbar.hpp"
#include "Root.hpp"

namespace Engine {

GuiProgressbar::GuiProgressbar() {}
GuiProgressbar::GuiProgressbar(std::string name) {
	mName = name;

	SetFont(sf::Font::GetDefaultFont());
	SetFontSize(12);
	SetFontStyle(sf::Text::Regular);
	SetFontColor(sf::Color::Black);
}
GuiProgressbar::~GuiProgressbar() {}
GuiProgressbar* GuiProgressbar::clone() const {
	return new GuiProgressbar();
}

void GuiProgressbar::SetProgress(const float progress) {
	mProgress = progress;
}

float GuiProgressbar::GetProgress() const {
	return mProgress;
}

void GuiProgressbar::SetTextVisible(bool visible) {
	mTextVisible = visible;
}

bool GuiProgressbar::GetTextVisible() const {
	return mTextVisible;
}

void GuiProgressbar::Draw(sf::RenderTarget* target) {
	mBackSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_back"));
	mBackSprite.SetPosition(mPosition.x, mPosition.y);
	mBackSprite.SetScale(mDimension.x, mDimension.y);
	target->Draw(mBackSprite);

	if(mProgress > 0) {
		mFrontSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_front"));
		mFrontSprite.SetPosition(mPosition.x, mPosition.y);
		mFrontSprite.SetScale(mDimension.x * mProgress, mDimension.y);
		target->Draw(mFrontSprite);
	}

	if(mTextVisible) {
		mText.SetString(boost::lexical_cast<std::string>(int(mProgress*100)) + "%");
		mText.SetPosition(int(mPosition.x + mDimension.x / 2 - mText.GetRect().Width / 2),
						  int(mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2) );

		target->Draw(mText);
	}

	DrawAllAttachments(target);
}

}
