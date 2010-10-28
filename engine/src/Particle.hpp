#ifndef PARTICLE_HPP 
#define PARTICLE_HPP

#include "Root.hpp"
#include "Entity.hpp"
#include "Vector2D.hpp"

namespace Engine {

class Particle : public Entity {
public:
	Particle();
	Particle(const Vector2D& pos,
			 const Vector2D& speed,
			 const sf::Color& color,
			 const float scale,
			 const PositionType pos_type = PositionType::POSITIONTYPE_WORLD);
	
	~Particle();

	Particle* clone() const;

	void Initialize();

    void Update(const float time_delta);

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

	const float GetLifeTime() const;

private:
	sf::Color mColor;
	float mScale;

	PositionType mPositionType;

	float mLifeTime;
};

}

#endif
