#include <boost/bind.hpp>

#include "ParticleEmitter.hpp"

namespace Engine {

ParticleEmitter::ParticleEmitter(const Vector2D& position_offset,
								 const float rotation_offset,
								 const float speed,
								 const float spread,
								 const float time_to_live,
								 const float rate,
								 const sf::Uint16 max_particles,
								 const sf::Blend::Mode mode,
								 const sf::Color& start_color,
								 const sf::Color& end_color,
								 const float start_scale,
								 const float end_scale) {
	mPositionOffset = position_offset;
	mRotationOffset = rotation_offset;
	mSpeed = speed;
	mSpread = spread;
	mTimeToLive = time_to_live;
	mRate = rate;
	mMaxParticles = max_particles;
	mStartColor = start_color;
	mEndColor = end_color;
	mStartScale = start_scale;
	mEndScale = end_scale;
}

ParticleEmitter::~ParticleEmitter() {}

ParticleEmitter* ParticleEmitter::clone() const {
	return new ParticleEmitter();
}

void ParticleEmitter::Initialize(const Vector2D& position_of_partsys,
								 const Vector2D& direction_of_partsys,
								 const PositionType pos_type_of_partsys) {
	mPosition = mPositionOffset + position_of_partsys;
	mDirection = direction_of_partsys;
	mDirection.Rotate(mRotationOffset);
	mPositionType = pos_type_of_partsys;
	mTimeSinceLastParticle = 0.f;
}

void ParticleEmitter::Update(const float time_delta,
							 const Vector2D& position_of_partsys,
							 const Vector2D& direction_of_partsys) {
	mPosition = mPositionOffset + position_of_partsys;
	mDirection = direction_of_partsys;
	mDirection.Rotate(mRotationOffset);
	std::cout << mParticles.size() << " meh: " << mTimeSinceLastParticle << std::endl;
	/*
	auto it = mParticles.begin();
	while(it != mParticles.end()) {
		if(it->GetLifeTime() >= mTimeToLive) {
			it = mParticles.erase(it);
		} else {
			++it;
		}
	}
	*/
	// The following line does the job of the commented code, nice!
	mParticles.erase_if(boost::bind(&Particle::GetLifeTime, _1) >= mTimeToLive);

	mTimeSinceLastParticle += time_delta;
	// Rate is amount of particles sent per second and time_delta is msecs.
	while(
		  mTimeSinceLastParticle >= 1.f / mRate) {
		float spread = sf::Randomizer::Random(-mSpread, mSpread);
		Vector2D spread_vector(1.f, spread);
		spread_vector.Rotate(mDirection.Rotation());
		Particle* particle = new Particle(mPosition, mDirection+spread_vector, mSpeed, mStartColor, mStartScale, mBlendMode, mPositionType);
		particle->Initialize();
		mParticles.push_back(particle);
		mTimeSinceLastParticle = 0.f;
	}

	BOOST_FOREACH(Particle& particle, mParticles)
		particle.Update(time_delta);
}

void ParticleEmitter::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const Particle& particle, mParticles)
		particle.Draw(target);
}

void ParticleEmitter::SetPositionOffset(const Vector2D& position_offset) {
	mPositionOffset = position_offset;
}

void ParticleEmitter::SetRotationOffset(const float position_offset) {
	mRotationOffset = position_offset;
}

void ParticleEmitter::SetSpeed(const float speed) {
	mSpeed = speed;
}

void ParticleEmitter::SetSpread(const float spread) {
	mSpread = spread;
}

void ParticleEmitter::SetTimeToLive(const float ttl) {
	mTimeToLive = ttl;
}

void ParticleEmitter::SetRate(const float rate) {
	mRate = rate;
}

void ParticleEmitter::SetMaxParticles(const Uint16 max_particles) {
	mMaxParticles = max_particles;
}

void ParticleEmitter::SetBlendMode(const sf::Blend::Mode mode) {
	mBlendMode = mode;

}

void ParticleEmitter::SetStartColor(const sf::Color& start_color) {
	mStartColor = start_color;
}

void ParticleEmitter::SetEndColor(const sf::Color& end_color) {
	mEndColor = end_color;
}

void ParticleEmitter::SetStartScale(const float start_scale) {
	mStartScale = start_scale;
}

void ParticleEmitter::SetEndScale(const float end_scale) {
	mEndScale = end_scale;
}

const Vector2D& ParticleEmitter::GetPositionOffset() const {
	return mPositionOffset;
}

const float ParticleEmitter::GetRotationOffset() const {
	return mRotationOffset;
}

const float ParticleEmitter::GetSpeed() const {
	return mSpeed;
}

const float ParticleEmitter::GetSpread() const {
	return mSpread;
}

const float ParticleEmitter::GetTimeToLive() const {
	return mTimeToLive;
}

const float ParticleEmitter::GetRate() const {
	return mRate;
}

const sf::Uint16 ParticleEmitter::GetMaxParticles() const {
	return mMaxParticles;
}

const sf::Blend::Mode ParticleEmitter::GetBlendMode() const {
	return mBlendMode;
}

const sf::Color& ParticleEmitter::GetStartColor() const {
	return mStartColor;
}

const sf::Color& ParticleEmitter::GetEndColor() const {
	return mEndColor;
}

const float ParticleEmitter::GetStartScale() const {
	return mStartScale;
}

const float ParticleEmitter::GetEndScale() const {
	return mEndScale;
}

sf::Uint16 ParticleEmitter::GetEntityId() const {
	return 50002;
}

Entity::PositionType ParticleEmitter::GetPositionType() const {
	return mPositionType;
}

}
