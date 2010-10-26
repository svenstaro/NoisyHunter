#include "Particle.hpp"

namespace Engine {

Particle::Particle() {}

Particle::Particle(const Vector2D& pos, 
				   const Vector2D& speed, 
				   const float time_to_live,
				   const sf::Color& start_color,
				   const sf::Color& end_color,
				   const float start_scale,
				   const float end_scale,
				   const PositionType pos_type) {
	mPosition = pos;
	mSpeed = speed;
	mTimeToLive = time_to_live;
	mStartColor = start_color;
	mEndColor = end_color;
	mStartScale = mStartScale;
	mEndScale = mEndScale;
	mPositionType = pos_type;
}

Particle::~Particle() {}

Particle* Particle::clone() const {
	return new Particle();
}

void Particle::Initialize() {
	sf::Sprite* d = new sf::Sprite(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("particle1"));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
}

void Particle::Update(const float time_delta) {
	mPosition += mSpeed * time_delta;
}

sf::Uint16 Particle::GetEntityId() const {
	return 50002;
}

Entity::PositionType Particle::GetPositionType() const {
	return mPositionType;
}

}
