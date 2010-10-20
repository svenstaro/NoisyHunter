#ifndef GUILABEL_HPP
#define GUILABEL_HPP

#include "GuiControl.hpp"

namespace Engine{

class GuiLabel : public GuiControl {
public:

	GuiLabel();

	GuiLabel(std::string name);

	~GuiLabel();

	GuiLabel* clone() const;

	void SetFont(const sf::Font& font);
	void SetFontSize(const float size);
	void SetFontStyle(unsigned long style);
	void SetFontColor(const sf::Color& color);

	virtual void Draw(sf::RenderTarget* target);

protected:
	sf::Text mText;
};

}
#endif // GUILABEL_HPP
