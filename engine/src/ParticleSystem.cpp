#include "ParticleSystem.hpp"

namespace Engine {

ParticleSystem::ParticleSystem() {}

ParticleSystem::ParticleSystem(const Vector2D pos, 
							   float rotation,
							   const PositionType pos_type) {
	mPosition = pos;
	mRotation = rotation;
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
	mParticleEmitters.push_back(emitter);
}

}
