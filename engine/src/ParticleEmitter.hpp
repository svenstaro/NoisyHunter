#ifndef PARTICLEEMITTER_HPP 
#define PARTICLEEMITTER_HPP

#include <boost/ptr_container/ptr_list.hpp>

#include "Entity.hpp"
#include "Particle.hpp"

namespace Engine {

class ParticleEmitter : public Entity {
public:
	ParticleEmitter(const Vector2D& position_offset = Vector2D(0.f, 0.f),
					const float rotation_offset = 0.f,
					const float speed = 0.1f,
					const float spread = 1.f,
					const float time_to_live = 3.f,
					const float rate = 10.f,
					const sf::Uint16 max_particles = 20,
					const sf::Color& start_color = sf::Color(0, 0, 255, 255),
					const sf::Color& end_color = sf::Color(255, 0, 0, 255),
					const float start_scale = 1.0f,
					const float end_scale = 2.0f);
	
	~ParticleEmitter();

	ParticleEmitter* clone() const;
	
	void Initialize(const Vector2D& position_of_partsys,
					const Vector2D& direction_of_partsys,
					const PositionType pos_type_of_partsys);

    void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

private:
	Vector2D mPositionOffset;
	float mRotationOffset;
	float mSpread;
	float mTimeToLive;
	float mRate;
	sf::Uint16 mMaxParticles;
	sf::Color mStartColor;
	sf::Color mEndColor;
	float mStartScale;
	float mEndScale;

	float mTimeSinceLastParticle;
	boost::ptr_list<Particle> mParticles;

	PositionType mPositionType;
};

}

#endif
