#ifndef GUIPROGRESSBAR_HPP
#define GUIPROGRESSBAR_HPP

#include <boost/lexical_cast.hpp>

#include "GuiLabel.hpp"
#include "TiledSprite.hpp"

namespace Engine {

class GuiProgressbar : public GuiLabel {
public:
	GuiProgressbar();
	GuiProgressbar(std::string name);
	~GuiProgressbar();
	GuiProgressbar* clone() const;

	// main callbacks
	virtual void Draw(sf::RenderTarget* target, Vector2D offset = Vector2D(0,0));

	void SetProgress(const float progress);
	float GetProgress() const;

	void SetTextVisible(bool visible);
	bool GetTextVisible() const;

private:
	float mProgress;
	TiledSprite mBackSprite;
	TiledSprite mFrontSprite;
	bool mTextVisible;
};

}

#endif
