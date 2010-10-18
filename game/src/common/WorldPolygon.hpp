#ifndef WORLDPOLYGON_HPP
#define WORLDPOLYGON_HPP

#include "Entity.hpp"

class WorldPolygon : public Engine::Entity {
public:
	WorldPolygon();

	~WorldPolygon();

	void Initialize();

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	sf::Uint16 GetEntityId() const;

private:

};

#endif
