#include "Particle.hpp"

namespace Engine {

Particle::Particle() {}

Particle::Particle(const Vector2D& position,
				   const Vector2D& direction,
				   const float speed,
				   const sf::Color& start_color,
				   const sf::Color& end_color,
				   const float start_scale,
				   const float end_scale,
				   const sf::Blend::Mode mode,
				   const PositionType pos_type) {
	mPosition = position;
	mDirection = direction;
	mSpeed = speed;
	mColor = start_color;
	mStartColor = start_color;
	mEndColor = end_color;
	mScale = start_scale;
	mStartScale = start_scale;
	mEndScale = end_scale;
	mBlendMode = mode;
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
	d->SetBlendMode(mBlendMode);
	mDrawable = d;
}

void Particle::Update(const float time_delta) {
	mLifeTime += time_delta;
	mPosition += mDirection * mSpeed * time_delta;
	mScale = ( mEndScale - mStartScale ) * mLifeTime;
	mDrawable->SetScale(mScale, mScale);
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_PARTICLE, boost::lexical_cast<std::string>(mScale));
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
