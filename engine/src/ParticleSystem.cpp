#include "ParticleSystem.hpp"

namespace Engine {

ParticleSystem::ParticleSystem() {}

ParticleSystem::ParticleSystem(const Vector2D& position,
							   const Vector2D& direction,
							   const PositionType pos_type) {
	mPosition = position;
	mDirection = direction;
	mPositionType = pos_type;
}

ParticleSystem::~ParticleSystem() {}

ParticleSystem* ParticleSystem::clone() const {
	return new ParticleSystem();
}

void ParticleSystem::Initialize() {
}

void ParticleSystem::Update(const float time_delta) {
	BOOST_FOREACH(ParticleEmitter& emitter, mParticleEmitters) {
		emitter.Update(time_delta);
	}
}

void ParticleSystem::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const ParticleEmitter& emitter, mParticleEmitters) {
		emitter.Draw(target);
	}
}

sf::Uint16 ParticleSystem::GetEntityId() const {
	return 50000;
}

Entity::PositionType ParticleSystem::GetPositionType() const {
	return mPositionType;
}

void ParticleSystem::AddEmitter(ParticleEmitter* emitter) {
	emitter->Initialize(mPosition, mDirection, mPositionType);
	mParticleEmitters.push_back(emitter);
}

}
