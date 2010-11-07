#include "GuiContainer.hpp"


namespace Engine {

GuiContainer* GuiContainer::clone() const {

}

bool GuiContainer::AddControl(GuiControl* control) {

}

void GuiContainer::Draw(sf::RenderTarget* target, Vector2D offset) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		control.Draw(target, offset + mPosition);
	}
}


}
