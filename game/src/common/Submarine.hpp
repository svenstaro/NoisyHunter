#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include <SFML/Graphics.hpp>

//#include "Root.hpp"
#include "Entity.hpp"
#include "Vector2D.hpp"
#include "Torpedo.hpp"
#include "SonarPing.hpp"

class Submarine : public Engine::Entity {
public:
    Submarine(float pos_x, float pos_y);
	~Submarine();


    void Update(float time_delta);
    // callbacks
    void OnCollide(const Engine::Entity& ent);
    void OnDamage(const float dmg);
    void OnFire();

    // controlling
    void SetTarget(const Engine::Vector2D target);

	const Engine::Entity* FireTorpedoTo(const Engine::Vector2D Pos);
	const Engine::Entity* PingTo(const Engine::Vector2D Pos);

	enum Mode {
		MODE_SILENT = 2000,
		MODE_NOISY = 2001
	};

private:
    Engine::Vector2D mTarget;
};

#endif
