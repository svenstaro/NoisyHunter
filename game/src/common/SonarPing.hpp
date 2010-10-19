#ifndef SONARPING_HPP
#define SONARPING_HPP

#include "Entity.hpp"

class SonarPing : public Engine::Entity {

public:
	SonarPing(const float direction_angle = 0);

	~SonarPing();

	SonarPing* clone() const;

	void Initialize();

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	sf::Uint16 GetEntityId() const;

private:
	sf::Uint16 mDirectionAngle;
};

#endif
