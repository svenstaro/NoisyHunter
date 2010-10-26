#include "GuiProgressbar.hpp"
#include "Root.hpp"

namespace Engine {

GuiProgressbar::GuiProgressbar() {}
GuiProgressbar::GuiProgressbar(std::string name) {
	mName = name;
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

void GuiProgressbar::Draw(sf::RenderTarget* target) {
	mFrontSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_front"));
	mBackSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.progressbar_back"));

	mBackSprite.SetPosition(mPosition.x, mPosition.y);
	mBackSprite.SetScale(mDimension.x, mDimension.y);

	mFrontSprite.SetPosition(mPosition.x, mPosition.y);
	mFrontSprite.SetScale(mDimension.x * mProgress, mDimension.y);

	mText.SetString(boost::lexical_cast<std::string>(int(mProgress*100)) + "%");
	mText.SetPosition(int(mPosition.x + mDimension.x / 2 - mText.GetRect().Width / 2), // convert to int to prevent blurry font due to half pixel coordinates
					  int(mPosition.y + mDimension.y / 2 - mText.GetRect().Height / 2) );

	target->Draw(mBackSprite);
	target->Draw(mFrontSprite);
	target->Draw(mText);
}

}
