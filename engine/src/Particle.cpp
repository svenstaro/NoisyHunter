#include "Particle.hpp"
#include <iostream>

namespace Engine {

Particle::Particle() {}

Particle::Particle(const Vector2D& position,
				   const Vector2D& direction,
				   const float speed,
				   const sf::Color& start_color,
				   const sf::Color& end_color,
				   const float start_alpha,
				   const float end_alpha,
				   const float start_scale,
				   const float end_scale,
				   const float time_to_live,
				   const sf::Blend::Mode mode,
				   const std::string& image_name,
				   const PositionType pos_type) {
	mPosition = position;
	mDirection = direction;
	mSpeed = speed;

	mColor = start_color;
	mStartColor = start_color;
	mEndColor = end_color;

	mAlpha = start_alpha;
	mStartAlpha = start_alpha;
	mEndAlpha = end_alpha;

	mScale = start_scale;
	mStartScale = start_scale;
	mEndScale = end_scale;

	mTimeToLive = time_to_live;
	mBlendMode = mode;
	mPositionType = pos_type;
	mLifeTime = 0;

	mImageName = image_name;
}

Particle::~Particle() {}

Particle* Particle::create() const {
	return new Particle();
}

void Particle::Initialize() {
	mLifeTime = 0.f;

	mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage(mImageName));
	mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);
	mSprite.SetBlendMode(mBlendMode);
}

void Particle::Update(const float time_delta) {
	if(mTimeToLive >= 0) {
		mLifeTime += time_delta;
		mPosition += mDirection * mSpeed * time_delta;
		float f = mLifeTime / mTimeToLive;
		// fix last frame, when lifetime > time to live
		if (f > 1)
			f = 1.f;

		mScale = ( mEndScale - mStartScale ) * f + mStartScale;

		int r = (mEndColor.r - mStartColor.r) * f + mStartColor.r;
		int g = (mEndColor.g - mStartColor.g) * f + mStartColor.g;
		int b = (mEndColor.b - mStartColor.b) * f + mStartColor.b;
		int a = (mEndAlpha - mStartAlpha) * f + mStartAlpha;

		mColor = sf::Color(r, g, b, a);

		mSprite.SetScale(mScale, mScale);
		mSprite.SetColor(mColor);
	}
	Engine::Vector2D p = Engine::Coordinates::WorldFloatToWorldPixel(mPosition);
	mSprite.SetPosition(p.x, p.y);
}

void Particle::Draw(sf::RenderTarget* target) const {
	target->Draw(mSprite);
}

sf::Uint16 Particle::GetEntityTypeId() const {
	return 50002;
}

Entity::PositionType Particle::GetPositionType() const {
	return mPositionType;
}

float Particle::GetLifeTime() const {
	return mLifeTime;
}

}
