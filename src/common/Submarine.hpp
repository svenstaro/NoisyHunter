#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"

class Submarine : Engine::Entity {
public:
    Submarine();
	~Submarine();

    // callbacks
    void OnCollide(const Engine::Entity& ent);
    void OnDamage(const float dmg);
    void OnFire();

	enum Mode {
		MODE_SILENT = 0,
		MODE_NOISY = 1
	}

private:
	
	
};

#endif
