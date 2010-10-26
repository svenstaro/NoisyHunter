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
	virtual void Draw(sf::RenderTarget* target);

	void SetProgress(const float progress);
	const float GetProgress() const;

private:
	float mProgress;
	TiledSprite mBackSprite;
	TiledSprite mFrontSprite;
};

}

#endif
