#include "ParticleEmitter.hpp"

namespace Engine {

ParticleEmitter::ParticleEmitter() {}

ParticleEmitter::~ParticleEmitter() {}

ParticleEmitter* ParticleEmitter::clone() const {
	return new ParticleEmitter();
}

void ParticleEmitter::Initialize() {
}

void ParticleEmitter::Update(const float time_delta) {
	BOOST_FOREACH(Particle& particle, mParticles) {
		particle.Update(time_delta);
	}
}

void ParticleEmitter::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const Particle& particle, mParticles) {
		particle.Draw(target);
	}
}

sf::Uint16 ParticleEmitter::GetEntityId() const {
	return 50002;
}

Entity::PositionType ParticleEmitter::GetPositionType() const {
	return mPositionType;
}

}
