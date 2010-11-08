#include <iostream>

#include "Entity.hpp"
#include "Root.hpp"
#include "EntityAttachment.hpp"

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
	packet & mSpeed;
	packet & mDirection.x;
	packet & mDirection.y;
}

sf::Packet Entity::PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate) {
    // Do not perform any action by default and return that nothing was
    // done at all.
    return sf::Packet();
}

void Entity::Update(const float time_delta) {
	mPosition += mSpeed * time_delta;
}

void Entity::UpdateAllAttachments(const float time_delta) {
	// Update EntityAttachments.
	BOOST_FOREACH(EntityAttachment attachment, mAttachments)
		attachment.Update(time_delta, mPosition, mDirection);
}

void Entity::Draw(sf::RenderTarget* target) const {
	// Set screen position.
	PositionType t = GetPositionType();
	Coordinates pos;
	if(t == Entity::POSITIONTYPE_WORLDPIXEL) {
		pos.SetWorldPixel(mPosition);
	} else if (t == Entity::POSITIONTYPE_SCREENPIXEL) {
		pos.SetScreenPixel(mPosition);
	} else if (t == Entity::POSITIONTYPE_VIEWPIXEL) {
		pos.SetViewPixel(mPosition);
	} else if (t == Entity::POSITIONTYPE_WORLDFLOAT) {
		pos.SetWorldFloat(mPosition);
	}
	Vector2D worldPos = pos.GetWorldPixel();
	Root::get_mutable_instance().SetRenderMode(RENDERMODE_WORLD);
	mDrawable->SetPosition(worldPos.x, worldPos.y);

	mDrawable->SetRotation(- Vector2D::rad2Deg( mDirection.Rotation() ));

	target->Draw(*mDrawable);

	DrawAllAttachments(target);
}

void Entity::DrawAllAttachments(sf::RenderTarget* target) const {
	// Update EntityAttachments.
	BOOST_FOREACH(EntityAttachment attachment, mAttachments)
		attachment.Draw(target);
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

void Entity::SetSpeed(const float speed) {
	mSpeed = speed;
}

void Entity::SetDirection(const Vector2D direction) {
	mDirection = direction;
	mDirection.Normalize();
}

const Vector2D Entity::GetPosition() const {
	return mPosition;
}

const float Entity::GetSpeed() const {
	return mSpeed;
}

const Vector2D Entity::GetDirection() const {
	return mDirection;
}

Entity::Layer Entity::GetLayer() const {
	return mLayer;
}

Entity::PositionType Entity::GetPositionType() const {
	return Entity::POSITIONTYPE_WORLDFLOAT;
}

void Entity::SetClientId(const sf::Uint16 client_id) {
    mClientId = client_id;
}

sf::Uint16 Entity::GetClientId() const {
    return mClientId;
}

void Entity::Attach(Entity& entity,
					const Vector2D& position_offset,
					const float rotation_offset,
					RestraintSettings restraint_settings) {
	EntityAttachment* attachment = new EntityAttachment(&entity, mPosition, mDirection, position_offset, rotation_offset, restraint_settings);
	//EntityAttachment* attachment = new EntityAttachment(&entity);
	mAttachments.push_back(attachment);
}

}
