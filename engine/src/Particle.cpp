#include "Particle.hpp"

namespace Engine {

Particle::Particle() {}

Particle::Particle(const Vector2D& position,
				   const float speed,
				   const sf::Color& color,
				   const float scale,
				   const PositionType pos_type) {
	mPosition = position;
	mSpeed = speed;
	mColor = color;
	mScale = scale;
	mPositionType = pos_type;
}

Particle::~Particle() {}

Particle* Particle::clone() const {
	return new Particle();
}

void Particle::Initialize() {
	mLifeTime = 0.f;

	sf::Sprite* d = new sf::Sprite(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("particle1"));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
}

void Particle::Update(const float time_delta) {
	mLifeTime += time_delta;
	mPosition += mSpeed * time_delta;
}

sf::Uint16 Particle::GetEntityId() const {
	return 50002;
}

Entity::PositionType Particle::GetPositionType() const {
	return mPositionType;
}

const float Particle::GetLifeTime() const {
	return mLifeTime;
}

}
