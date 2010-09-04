#ifndef SONARPING_HPP
#define SONARPING_HPP

#include "Entitiy.hpp"

class SonarPing : Engine::Entity {

public:
	SonarPing();
	~SonarPing();

	// callbacks
	void OnCollide(const Engine::Entity& ent);
	

private:	

};

#endif
