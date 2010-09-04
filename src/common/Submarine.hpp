#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"
#include "Torpedo.hpp"

class Submarine : Engine::Entity {
public:
    Submarine();
	~Submarine();

    // callbacks
    void OnCollide(const Engine::Entity& ent);
    void OnDamage(const float dmg);
    void OnFire();

	const Engine::Entity& FireTorpedoTo(const Engine::Vector2D Pos);
	const Engine::Entity& PingTo(const Engine::Vector2D Pos);

	enum Mode {
		MODE_SILENT = 2000,
		MODE_NOISY = 2001
	}

private:
	
	
};

#endif
