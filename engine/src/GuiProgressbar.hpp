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
	GuiProgressbar* create() const;

	// main callbacks
	virtual void Draw(sf::RenderTarget* target);

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
