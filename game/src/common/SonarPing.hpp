#ifndef SONARPING_HPP
#define SONARPING_HPP

#include "Entity.hpp"

class SonarPing : public Engine::Entity {

public:
	SonarPing();
	SonarPing(float direction_angle);
	~SonarPing();

	// callbacks
	void OnCollide(const Engine::Entity& ent);


private:

};

#endif
