#include "GuiControl.hpp"
#include "Root.hpp"

namespace Engine {

GuiControl::GuiControl(const sf::Uint16 entity_unique_id, 
					   const std::string& name) {
	mEntityUniqueId = entity_unique_id;
    mName = name;
	SetPositionType(Entity::PositionType::POSITIONTYPE_SCREENPIXEL);
    SetFocus(false);
    SetHover(false);
}

GuiControl::~GuiControl() {}

GuiControl* GuiControl::create() const {}

void GuiControl::Update(const float time_delta) {
	UpdateAllAttachments(time_delta);
}

// === EVENT SIGNAL BINDING ===
void GuiControl::BindOnMouseDown(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)>::slot_type& slot) {
	mOnMouseDownSignal.connect(slot);
}

void GuiControl::BindOnMouseUp(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)>::slot_type& slot) {
	mOnMouseUpSignal.connect(slot);
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
void GuiControl::TriggerOnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	mOnMouseDownSignal(mouse_x, mouse_y, mouse_button);
}

void GuiControl::TriggerOnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
	mOnMouseUpSignal(mouse_x, mouse_y, mouse_button);
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

void GuiControl::OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {}

void GuiControl::OnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {}

void GuiControl::OnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y) {}

void GuiControl::OnKeyDown(const sf::Key::Code key) {}

void GuiControl::OnKeyUp(const sf::Key::Code key) {}

void GuiControl::OnType(const sf::Uint32 unicode_char) {}

sf::Uint16 GuiControl::GetEntityTypeId() const {
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

Entity::PositionType GuiControl::GetPositionType() const {
	return mPositionType;
}

void GuiControl::SetPositionType(Entity::PositionType position_type) {
	mPositionType = position_type;
}

}
