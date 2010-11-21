#ifndef SONARPING_HPP
#define SONARPING_HPP

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "Entity.hpp"
#include "EntityTypeId.hpp"
#include "Vector2D.hpp"
#include "ParticleSystem.hpp"

class SonarPing : public Engine::Entity {

public:
	SonarPing(const Engine::Vector2D& pos = Engine::Vector2D(0,0),
			  const Engine::Vector2D& direction = Engine::Vector2D(0, 1),
			  const float time_to_live = 3.f,
			  const float speed = 0.3f);

	~SonarPing();

	SonarPing* clone() const;

	void Initialize();

	void Update(const float time_delta);

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	sf::Uint16 GetEntityTypeId() const;

	void serialize(Engine::IOPacket& packet);

	void SetTimeToLive(const sf::Uint16 time_to_live);

private:
};

#endif
