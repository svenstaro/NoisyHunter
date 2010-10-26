#include <iostream>

#include "Entity.hpp"
#include "Root.hpp"

namespace Engine {

Entity::Entity() {}

Entity::~Entity() {}

Entity* Entity::clone() const {}

void Entity::Initialize() {}

void Entity::GrabUniqueId() {
	mUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

void Entity::OnCollide(const Entity& ent) {}

bool Entity::operator<(const Entity& other) {
	return mLayer < other.GetLayer();
}

void Entity::serialize(IOPacket& packet) {
	packet & mClientId;
    packet & mUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
    packet & mSpeed.x;
	packet & mSpeed.y;
}

sf::Packet Entity::PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate) {
    // Do not perform any action by default and return that nothing was
    // done at all.
    return sf::Packet();
}

void Entity::Update(const float time_delta) {
	mPosition += mSpeed * time_delta;
}

void Entity::Draw(sf::RenderTarget* target) const {
	// Set screen position.
	if(GetPositionType() == Entity::POSITIONTYPE_WORLD) {
		// Convert to world coordinates.
		Coordinates pos = Root::get_mutable_instance().GetInputManagerPtr()->GetScreenCoordinates(mPosition.x, mPosition.y);
		mDrawable->SetPosition(pos.ScreenX, pos.ScreenY);
	} else if(GetPositionType() == Entity::POSITIONTYPE_SCREEN) {
		// Simply use screen coordinates.
		mDrawable->SetPosition(mPosition.x, mPosition.y);
	}

	float rotation = 0;
	if(mSpeed.x != 0 && mSpeed.y != 0)
		rotation = mSpeed.Rotation();

	mDrawable->SetRotation(- Vector2D::rad2Deg(rotation));

	target->Draw(*mDrawable);
}

sf::Uint16 Entity::GetUniqueId() const {
	return mUniqueId;
}

void Entity::SetPosition(const float x, const float y) {
	SetPosition(Vector2D(x, y));
}

void Entity::SetPosition(const Vector2D position) {
	mPosition = position;
}

void Entity::SetSpeed(const float x, const float y) {
	mSpeed = Vector2D(x, y);
}

void Entity::SetRotation(const float degree) {
	mRotation = degree;
}

const Vector2D Entity::GetPosition() const {
	return mPosition;
}

const Vector2D Entity::GetSpeed() const {
	return mSpeed;
}

const float Entity::GetRotation() const {
	return mRotation;
}

Entity::Layer Entity::GetLayer() const {
	return mLayer;
}

Entity::PositionType Entity::GetPositionType() const {
	return Entity::POSITIONTYPE_WORLD;
}

void Entity::SetClientId(const sf::Uint16 client_id) {
    mClientId = client_id;
}
sf::Uint16 Entity::GetClientId() const {
    return mClientId;
}

}
