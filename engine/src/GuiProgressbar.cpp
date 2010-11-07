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

const float GuiProgressbar::GetProgress() const {
	return mProgress;
}

void GuiProgressbar::Draw(sf::RenderTarget* target, Vector2D offset) {
	mFrontSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_front"));
	mBackSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_back"));

	mBackSprite.SetPosition(mPosition.x + offset.x, mPosition.y + offset.y);
	mBackSprite.SetScale(mDimension.x, mDimension.y);

	mFrontSprite.SetPosition(mPosition.x + offset.x, mPosition.y + offset.y);
	mFrontSprite.SetScale(mDimension.x * mProgress, mDimension.y);

	mText.SetString(boost::lexical_cast<std::string>(int(mProgress*100)) + "%");
	mText.SetPosition(offset.x + int(mPosition.x + mDimension.x / 2 - mText.GetRect().Width / 2),
					  offset.y + int(mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2) );

	target->Draw(mBackSprite);
	target->Draw(mFrontSprite);
	target->Draw(mText);

	DrawAllAttachments(target);
}

}
