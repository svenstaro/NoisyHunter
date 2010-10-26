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
			 const float time_to_live,
			 const sf::Color& start_color = sf::Color(0, 0, 255, 255),
			 const sf::Color& end_color = sf::Color(255, 0, 0, 255),
			 const float start_scale = 1.0f,
			 const float end_scale = 2.0f,
			 const PositionType pos_type = PositionType::POSITIONTYPE_WORLD);
	
	~Particle();

	Particle* clone() const;

	void Initialize();

    void Update(const float time_delta);

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

private:
	float mTimeToLive;
	sf::Color mStartColor;
	sf::Color mEndColor;
	float mStartScale;
	float mEndScale;
	PositionType mPositionType;
};

}

#endif
