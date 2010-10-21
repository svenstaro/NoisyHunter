#include "GuiProgressbar.hpp"

namespace Engine {

GuiProgressbar::GuiProgressbar() {}
GuiProgressbar::GuiProgressbar(std::string name) {
	mName = name;
}
GuiProgressbar::~GuiProgressbar() {}
GuiProgressbar* GuiProgressbar::clone() const {
	return new GuiProgressbar();
}
void GuiProgressbar::Draw(sf::RenderTarget* target) {

}

}
