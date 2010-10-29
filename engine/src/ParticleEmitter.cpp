#include <boost/bind.hpp>

#include "ParticleEmitter.hpp"

namespace Engine {

ParticleEmitter::ParticleEmitter(const Vector2D& offset,
					const Vector2D& speed,
					const float spread,
					const float time_to_live,
					const sf::Uint16 max_particles,
					const sf::Color& start_color,
					const sf::Color& end_color,
					const float start_scale,
					const float end_scale) {
	mOffset = offset;
	mSpeed = speed;
	mSpread = spread;
	mTimeToLive = time_to_live;
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

void ParticleEmitter::Initialize(const PositionType pos_type) {
	mPositionType = pos_type;
}

void ParticleEmitter::Update(const float time_delta) {
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

	while(mParticles.size() < mMaxParticles) {
		Particle* particle = new Particle(mOffset, mSpeed, mStartColor, mStartScale, mPositionType);
		particle->Initialize();
		mParticles.push_back(particle);
	}

	BOOST_FOREACH(Particle& particle, mParticles)
		particle.Update(time_delta);
}

void ParticleEmitter::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const Particle& particle, mParticles)
		particle.Draw(target);
}

sf::Uint16 ParticleEmitter::GetEntityId() const {
	return 50002;
}

Entity::PositionType ParticleEmitter::GetPositionType() const {
	return mPositionType;
}

}
