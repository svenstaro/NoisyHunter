#ifndef PARTICLE_HPP 
#define PARTICLE_HPP

#include <string>

#include "Root.hpp"
#include "Entity.hpp"
#include "Vector2D.hpp"
#include "boost/lexical_cast.hpp"

namespace Engine {

class Particle : public Entity {
public:
	Particle();
	Particle(const Vector2D& position,
			 const Vector2D& direction,
			 const float speed,
			 const sf::Color& start_color,
			 const sf::Color& end_color,
			 const float start_alpha,
			 const float end_alpha,
			 const float start_scale,
			 const float end_scale,
			 const float time_to_live,
			 const sf::Blend::Mode mode,
			 const std::string& image_name,
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
	sf::Color mStartColor;
	sf::Color mEndColor;
	float mAlpha;			// 100% = visible
	float mStartAlpha;
	float mEndAlpha;
	float mScale;
	float mStartScale;
	float mEndScale;

	sf::Blend::Mode mBlendMode;

	PositionType mPositionType;

	float mLifeTime;
	float mTimeToLive;
	std::string mImageName;
};

}

#endif
