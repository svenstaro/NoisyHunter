#include "ParticleSystem.hpp"

namespace Engine {

ParticleSystem::ParticleSystem(const Vector2D& position,
							   const Vector2D& direction,
							   const PositionType pos_type) {
	mPosition = position;
	mDirection = direction;
	mPositionType = pos_type;
}

ParticleSystem::~ParticleSystem() {}

ParticleSystem* ParticleSystem::create() const {
	return new ParticleSystem();
}

void ParticleSystem::Initialize() {
}

void ParticleSystem::Update(const float time_delta) {
	BOOST_FOREACH(ParticleEmitter& emitter, mParticleEmitters) {
		emitter.Update(time_delta, mPosition, mDirection);
	}
	UpdateAllAttachments(time_delta);
}

void ParticleSystem::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const ParticleEmitter& emitter, mParticleEmitters) {
		emitter.Draw(target);
	}
	DrawAllAttachments(target);
}

sf::Uint16 ParticleSystem::GetEntityTypeId() const {
	return 50000;
}

Entity::PositionType ParticleSystem::GetPositionType() const {
	return mPositionType;
}

void ParticleSystem::AddEmitter(ParticleEmitter* emitter) {
	emitter->Initialize(mPosition, mDirection, mPositionType);
	mParticleEmitters.push_back(emitter);
}

void ParticleSystem::SetPosition(const Vector2D& position) {
	mPosition = position;
}

void ParticleSystem::SetDirection(const Vector2D& direction) {
	mDirection = direction;
}

void ParticleSystem::SetPositionType(const PositionType pos_type) {
	mPositionType = pos_type;
}

}
