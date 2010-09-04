#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Vector2D.hpp"

namespace Engine {

class Entity {

public:
	Entity();
	virtual ~Entity() = 0;

	virtual void OnCollide(const Entity& ent);
	
	void SetSpeed(const float x, const float y);
	void SetPosition(const float x, const float y);

	const Vector2D GetSpeed() const;
	const Vector2D GetPosition() const;

private:

	Vector2D mPosition;
	Vector2D mSpeed;
};

}

#endif
