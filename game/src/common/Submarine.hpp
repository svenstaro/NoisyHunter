#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "IOPacket.hpp"
#include "Vector2D.hpp"
#include "Torpedo.hpp"
#include "SonarPing.hpp"

class Submarine : public Engine::Entity {
public:
    Submarine(const float pos_x = 0,
			  const float pos_y = 0,
			  const sf::Uint16 client_id = -1);

	~Submarine();

	Submarine* clone() const;

	void Initialize();

    void Update(float time_delta);

    // callbacks
    void OnCollide(const Engine::Entity& ent);

    void OnDamage(const float dmg);

    void OnFire();
    
    sf::Packet PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate = false);

	sf::Uint16 GetEntityId() const;

    // controlling
	void SetTarget(const float x, const float y);
    void SetTarget(const Engine::Vector2D target);

	const Engine::Entity* FireTorpedoTo(const Engine::Vector2D Pos);

	const Engine::Entity* PingTo(const Engine::Vector2D Pos);

    void serialize(Engine::IOPacket& packet);

	enum Mode {
		MODE_SILENT = 2000,
		MODE_NOISY = 2001
	};

private:
    Engine::Vector2D mTarget;
};

#endif
