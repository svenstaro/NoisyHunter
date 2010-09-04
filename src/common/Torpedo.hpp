#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entitiy.hpp"

class Torpedo : Engine::Entity {

public:
	Torpedo(Engine::Vector2D Pos, Engine::Vector2D Speed);
	~Torpedo();

	// callbacks
	void OnCollide(const Engine::Entity& ent);
	void OnDeath();

};

#endif
