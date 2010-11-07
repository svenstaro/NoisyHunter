#include "GuiContainer.hpp"


namespace Engine {

GuiContainer::~GuiContainer() {}

GuiContainer* GuiContainer::clone() const {
	return new GuiContainer();
}

bool GuiContainer::AddControl(GuiControl* control) {
	mControls.push_back(control);
}

void GuiContainer::Draw(sf::RenderTarget* target, Vector2D offset) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		control.Draw(target, offset + mPosition);
	}
}


}
