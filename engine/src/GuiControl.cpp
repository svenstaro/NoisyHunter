#include "GuiControl.hpp"
#include "Root.hpp"

namespace Engine {

GuiControl::GuiControl(const sf::Uint16 unique_id, 
					   const std::string& name) {
	mUniqueId = unique_id;
    mName = name;
    SetFocus(false);
    SetHover(false);
}

GuiControl::~GuiControl() {}

GuiControl* GuiControl::clone() const {}

void GuiControl::Update(const float time_delta) {}

// === EVENT SIGNAL BINDING ===
void GuiControl::BindOnClick(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)>::slot_type& slot) {
    mOnClickSignal.connect(slot);
}

void GuiControl::BindOnMouseMove(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y)>::slot_type& slot) {
    mOnMouseMoveSignal.connect(slot);
}

void GuiControl::BindOnKeyDown(const boost::signals2::signal<void (const sf::Key::Code key)>::slot_type& slot) {
    mOnKeyDownSignal.connect(slot);
}

void GuiControl::BindOnKeyUp(const boost::signals2::signal<void (const sf::Key::Code key)>::slot_type& slot) {
    mOnKeyUpSignal.connect(slot);
}

void GuiControl::BindOnType(const boost::signals2::signal<void (const sf::Uint32 unicode_char)>::slot_type& slot) {
    mOnTypeSignal.connect(slot);
}

// === EVENT SIGNAL TRIGGERS ===
void GuiControl::TriggerOnClick(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
    mOnClickSignal(mouse_x, mouse_y, mouse_button);
}

void GuiControl::TriggerOnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y) {
    mOnMouseMoveSignal(mouse_x, mouse_y);
}

void GuiControl::TriggerOnKeyDown(const sf::Key::Code key) {
    mOnKeyDownSignal(key);
}

void GuiControl::TriggerOnKeyUp(const sf::Key::Code key) {
    mOnKeyUpSignal(key);
}

void GuiControl::TriggerOnType(const sf::Uint32 unicode_char) {
    mOnTypeSignal(unicode_char);
}


// === EVENT CALLBACKS FOR INTERNAL USE ===

void GuiControl::OnClick(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_GUI, "Clicked on element.");
}

void GuiControl::OnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y) {
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_GUI, "Moved over element.");
}

void GuiControl::OnKeyDown(const sf::Key::Code key) {
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_GUI, "Pressed key on element.");
}

void GuiControl::OnKeyUp(const sf::Key::Code key) {
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_GUI, "Released key on element.");
}

void GuiControl::OnType(const sf::Uint32 unicode_char) {
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_GUI, "Typed into element.");
}

sf::Uint16 GuiControl::GetEntityId() const {
	return 60000;
}

bool GuiControl::IsAtPoint(const Vector2D point) {
    return (point.x >= mPosition.x and
            point.y >= mPosition.y and
            point.x <= mPosition.x + mDimension.x and
            point.y <= mPosition.y + mDimension.y);
}

void GuiControl::SetFocus(bool is_focused) {
    mIsFocused = is_focused;
}

bool GuiControl::HasFocus() const {
    return mIsFocused;
}

void GuiControl::SetHover(bool hover) {
    mHover = hover;
}

Entity::PositionType GuiControl::GetPositionType() const {
    return Entity::POSITIONTYPE_SCREEN;
}

const Vector2D GuiControl::GetPosition() const {
    return mPosition;
}

void GuiControl::SetDimension(const Vector2D dimension) {
    mDimension = dimension;
}

const Vector2D GuiControl::GetDimension() const {
    return mDimension;
}

void GuiControl::SetText(std::string text) {
    mCaption = text;
}

const std::string GuiControl::GetText() const {
    return mCaption;
}

const std::string GuiControl::GetName() const {
    return mName;
}

}
