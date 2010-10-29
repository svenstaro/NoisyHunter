#ifndef PARTICLEEMITTER_HPP 
#define PARTICLEEMITTER_HPP

#include <boost/ptr_container/ptr_list.hpp>

#include "Entity.hpp"
#include "Particle.hpp"

namespace Engine {

class ParticleEmitter : public Entity {
public:
	ParticleEmitter(const Vector2D& offset = Vector2D(0.f, 0.f),
					const float speed = 0.5f,
					const float spread = 0.1f,
					const float time_to_live = 3.f,
					const sf::Uint16 max_particles = 20,
					const sf::Color& start_color = sf::Color(0, 0, 255, 255),
					const sf::Color& end_color = sf::Color(255, 0, 0, 255),
					const float start_scale = 1.0f,
					const float end_scale = 2.0f);
	
	~ParticleEmitter();

	ParticleEmitter* clone() const;
	
	void Initialize(PositionType);

    void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

private:
	Vector2D mOffset;
	Vector2D mSpeed;
	float mSpread;
	float mTimeToLive;
	sf::Uint16 mMaxParticles;
	sf::Color mStartColor;
	sf::Color mEndColor;
	float mStartScale;
	float mEndScale;

	boost::ptr_list<Particle> mParticles;

	PositionType mPositionType;
};

}

#endif
