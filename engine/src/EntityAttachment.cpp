#include "EntityAttachment.hpp"
#include "Entity.hpp"

namespace Engine {

EntityAttachment::EntityAttachment(Entity* entity,
								   const Vector2D& position,
								   const Vector2D& direction,
								   const Vector2D& position_offset,
								   const float rotation_offset) {
	mEntity = entity;
	mPosition = position + position_offset;
	mPositionOffset = position_offset;
	mDirection = direction;
	mDirection.Rotate(rotation_offset);
	mRotationOffset = rotation_offset;
}

EntityAttachment::~EntityAttachment() {}

void EntityAttachment::Update(const float time_delta, 
							  const Vector2D& position, 
							  const Vector2D& direction) {
	mEntity->Update(time_delta);
	mPosition = position + mPositionOffset;
	mDirection = direction;
	mDirection.Rotate(mRotationOffset);
	mEntity->SetPosition(mPosition);
	mEntity->SetDirection(mDirection);
}

void EntityAttachment::Draw(sf::RenderTarget* target) {
	mEntity->Draw(target);
}

}
