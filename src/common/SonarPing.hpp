#ifndef SONARPING_HPP
#define SONARPING_HPP

#include "Entity.hpp"

class SonarPing : public Engine::Entity {

public:
	SonarPing();
	~SonarPing();

	// callbacks
	void OnCollide(const Engine::Entity& ent);


private:

};

#endif
