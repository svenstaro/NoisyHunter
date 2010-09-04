#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"

class Torpedo : public Engine::Entity {

public:
	Torpedo();
	Torpedo(Engine::Vector2D pos, Engine::Vector2D speed, Engine::Vector2D target_position);
	~Torpedo();

	// callbacks
	void OnCollide(const Engine::Entity& ent);
	void OnDeath();

	void Update(const float time_delta);

private:
	Engine::Vector2D mTargetPosition;
};

#endif
