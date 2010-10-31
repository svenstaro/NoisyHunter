#ifndef ENTITYATTACHMENT_HPP
#define ENTITYATTACHMENT_HPP

#include "Vector2D.hpp"

namespace Engine {

// Forward declare Entity :(
class Entity;
class EntityAttachment {
public:
	EntityAttachment(Entity* entity,
					 const Vector2D& position,
					 const Vector2D& direction,
					 const Vector2D& position_offset,
					 const float rotation_offset);

	~EntityAttachment();

	void Update(const float time_delta, 
				const Vector2D& position, 
				const Vector2D& direction);

private:
	Vector2D mPosition;
	Vector2D mPositionOffset;
	Vector2D mDirection;
	float mRotationOffset;

	Entity* mEntity;
};

}

#endif
