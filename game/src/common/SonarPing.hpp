#ifndef SONARPING_HPP
#define SONARPING_HPP

#include "Entity.hpp"

class SonarPing : public Engine::Entity {

public:
	SonarPing(const sf::Uint16 unique_id = 0, 
			  const float direction_angle = 0);

	~SonarPing();

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	sf::Uint16 GetEntityId() const;

private:
	sf::Uint16 mDirectionAngle;
};

#endif
