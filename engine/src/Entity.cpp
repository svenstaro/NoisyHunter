#include <iostream>

#include "Entity.hpp"
#include "Root.hpp"

namespace Engine {

Entity::Entity() {}

Entity::~Entity() {}

void Entity::OnCollide(const Entity& ent) {}

bool Entity::operator<(const Entity& other) {
	return mLayer < other.GetLayer();
}

void Entity::serialize(IOPacket& packet) {
    packet & mUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
    packet & mSpeed.x;
    packet & mSpeed.y;
    sf::Uint16 l = mLayer;
    packet & l;
}

void Entity::Update(const float time_delta) {
	mPosition += mSpeed * time_delta;
}

void Entity::Draw(sf::RenderTarget* target) const {
	// set screen position
	if(GetPositionType() == Entity::POSITIONTYPE_WORLD) {
		// convert to world coordinates
		Coordinates pos = Root::get_mutable_instance().GetInputManagerPtr()->GetScreenCoordinates(mPosition.x, mPosition.y);
		mDrawable->SetPosition(pos.ScreenX, pos.ScreenY);
	} else if(GetPositionType() == Entity::POSITIONTYPE_SCREEN) {
		// simply use screen coordinates
		mDrawable->SetPosition(mPosition.x, mPosition.y);
	}

	float rotation = 0;
	if (mSpeed.x != 0 && mSpeed.y != 0)
		rotation = mSpeed.Rotation();

	mDrawable->SetRotation(- Vector2D::rad2Deg(rotation));

	target->Draw(*mDrawable);
}

sf::Uint16 Entity::GetUniqueId() const {
	return mUniqueId;
}

void Entity::SetSpeed(const float x, const float y) {
	mSpeed = Vector2D(x, y);
}

void Entity::SetPosition(const float x, const float y) {
	mPosition = Vector2D(x, y);
}

const Vector2D Entity::GetSpeed() const {
	return mSpeed;
}

const Vector2D Entity::GetPosition() const {
	return mPosition;
}

Entity::Layer Entity::GetLayer() const {
	return mLayer;
}

Entity::PositionType Entity::GetPositionType() const {
	return Entity::POSITIONTYPE_WORLD;
}

}
