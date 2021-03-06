#ifndef RADAR_HPP
#define RADAR_HPP

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "Entity.hpp"
#include "EntityTypeId.hpp"

class Radar : public Engine::Entity {

public:
	Radar();
	~Radar();

	Radar* create() const;

	void Initialize();

	void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	Engine::Entity::PositionType GetPositionType() const;

	sf::Uint16 GetEntityTypeId() const;

private:
	sf::Sprite mBackground;
	sf::Sprite mRay;
};

#endif
