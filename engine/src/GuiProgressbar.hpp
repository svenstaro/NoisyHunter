#ifndef GUIPROGRESSBAR_HPP
#define GUIPROGRESSBAR_HPP

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

private:
	TiledSprite mBackSprite;
	TiledSprite mFrontSprite;
};

}

#endif
