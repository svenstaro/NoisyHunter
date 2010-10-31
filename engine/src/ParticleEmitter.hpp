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
					const float speed = 60.f,
					const float spread = 90.f,
					const float time_to_live = 3.f,
					const float rate = 10.f,
					const sf::Blend::Mode = sf::Blend::Multiply,
					const sf::Color& start_color = sf::Color(255, 255, 255, 255),
					const sf::Color& end_color = sf::Color(170, 200, 255, 255),
					const float start_alpha = 255,
					const float end_alpha = 255,
					const float start_scale = 1.0f,
					const float end_scale = 2.0f);
	
	~ParticleEmitter();

	ParticleEmitter* clone() const;
	
	void Initialize(const Vector2D& position_of_partsys,
					const Vector2D& direction_of_partsys,
					const PositionType pos_type_of_partsys);

    void Update(const float time_delta,
				const Vector2D& position_of_partsys,
				const Vector2D& direction_of_partsys);

	void Draw(sf::RenderTarget* target) const;

	void SetPositionOffset(const Vector2D& position_offset);
	void SetRotationOffset(const float position_offset);
	void SetSpeed(const float speed);
	void SetSpread(const float spread);
	void SetTimeToLive(const float ttl);
	void SetRate(const float rate);
	void SetBlendMode(const sf::Blend::Mode mode);
	void SetStartColor(const sf::Color& start_color);
	void SetEndColor(const sf::Color& end_color);
	void SetStartAlpha(const float start_alpha);
	void SetEndAlpha(const float end_alpha);
	void SetStartScale(const float start_scale);
	void SetEndScale(const float end_scale);

	const Vector2D& GetPositionOffset() const;
	const float GetRotationOffset() const;
	const float GetSpeed() const;
	const float GetSpread() const;
	const float GetTimeToLive() const;
	const float GetRate() const;
	const sf::Blend::Mode GetBlendMode() const;
	const sf::Color& GetStartColor() const;
	const sf::Color& GetEndColor() const;
	const float GetStartAlpha() const;
	const float GetEndAlpha() const;
	const float GetStartScale() const;
	const float GetEndScale() const;

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

private:
	Vector2D mPositionOffset;
	float mRotationOffset;
	float mSpread;
	float mTimeToLive;
	float mRate;
	sf::Blend::Mode mBlendMode;
	sf::Color mStartColor;
	sf::Color mEndColor;
	float mStartAlpha;
	float mEndAlpha;
	float mStartScale;
	float mEndScale;

	float mTimeSinceLastParticle;
	boost::ptr_list<Particle> mParticles;

	PositionType mPositionType;
};

}

#endif
