#ifndef WORLDPOLYGON_HPP
#define WORLDPOLYGON_HPP

#include "Entity.hpp"

class WorldPolygon : Engine::Entity {
public:
	WorldPolygon();
	~WorldPolygon();

	// callbacks
	void OnCollide(const Engine::Entity& ent);
	
private:

};

#endif
