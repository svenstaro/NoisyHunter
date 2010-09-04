#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entitiy.hpp"
#include "Vector2D.hpp"

class Torpedo : Engine::Entity {

public:
	Torpedo();
	Torpedo(Engine::Vector2D pos, Engine::Vector2D speed);
	~Torpedo();

	// callbacks
	void OnCollide(const Engine::Entity& ent);
	void OnDeath();

	void Update(const float time_delta);

private:
	Engine::Vector2D mTargetPosition;
};

#endif
