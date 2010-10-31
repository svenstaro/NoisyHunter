#ifndef PARTICLE_HPP 
#define PARTICLE_HPP

#include "Root.hpp"
#include "Entity.hpp"
#include "Vector2D.hpp"

namespace Engine {

class Particle : public Entity {
public:
	Particle();
	Particle(const Vector2D& position,
			 const Vector2D& direction,
			 const float speed,
			 const sf::Color& color,
			 const float scale,
			 const sf::Blend::Mode mode,
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
	sf::Blend::Mode mBlendMode;

	PositionType mPositionType;

	float mLifeTime;
};

}

#endif
