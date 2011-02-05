#include "GuiContainer.hpp"


namespace Engine {

GuiContainer::~GuiContainer() {}


bool GuiContainer::AddControl(GuiControl* control) {
	mControls.push_back(control);
	PlaceChildren();
	return true;
}

void GuiContainer::SetPosition(const float x, const float y) {
	GuiControl::SetPosition(x,y);
	PlaceChildren();
}

void GuiContainer::SetPosition(const Vector2D position) {
	GuiControl::SetPosition(position);
	PlaceChildren();
}

void GuiContainer::SetDimension(const Vector2D dimension) {
	GuiControl::SetDimension(dimension);
	PlaceChildren();
}


void GuiContainer::Update(float time_delta) {
	UpdateAllAttachments(time_delta);
}

void GuiContainer::Draw(sf::RenderTarget* target) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		control.Draw(target);
	}
}


// INTERNAL EVENT CALLBACKS FOR REDIRECTION TO CHILD ENTITIES

void GuiContainer::OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		if(control.IsAtPoint(Vector2D(mouse_x, mouse_y))) {
			control.OnMouseDown(mouse_x, mouse_y, mouse_button);
			control.TriggerOnMouseDown(mouse_x, mouse_y, mouse_button);
		}
	}
}

void GuiContainer::OnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		if(control.IsAtPoint(Vector2D(mouse_x, mouse_y))) {
			control.OnMouseUp(mouse_x, mouse_y, mouse_button);
			control.TriggerOnMouseUp(mouse_x, mouse_y, mouse_button);
		}
	}
}

void GuiContainer::OnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		control.SetHover(control.IsAtPoint(Vector2D(mouse_x, mouse_y)));
		if(control.IsAtPoint(Vector2D(mouse_x, mouse_y))) {
			control.OnMouseMove(mouse_x, mouse_y);
			control.TriggerOnMouseMove(mouse_x, mouse_y);
		}
	}
}

void GuiContainer::OnKeyDown(const sf::Key::Code key) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		if(control.HasFocus()) {
			control.OnKeyDown(key);
			control.TriggerOnKeyDown(key);
		}
	}
}

void GuiContainer::OnKeyUp(const sf::Key::Code key) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		if(control.HasFocus()) {
			control.OnKeyUp(key);
			control.TriggerOnKeyUp(key);
		}
	}
}

void GuiContainer::OnType(const sf::Uint32 unicode_char) {
	BOOST_FOREACH(GuiControl& control, mControls) {
		if(control.HasFocus()) {
			control.OnType(unicode_char);
			control.TriggerOnType(unicode_char);
		}
	}
}


}
