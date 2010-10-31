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
				   const float time_to_live,
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
	mTimeToLive = time_to_live;
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
	mScale = ( mEndScale - mStartScale ) * mLifeTime/mTimeToLive;
	int r =  mEndColor.r-mStartColor.r;
	int g =  mEndColor.g-mStartColor.g;
	int b =  mEndColor.b-mStartColor.b;
	const float f = mLifeTime/mTimeToLive;
	mColor = sf::Color(r * f, g * f, b * f, 255) + mStartColor;
	//std::cout << mColor.r << "|" << mColor.g << "|" << mColor.b << "|" << mColor.a << std::endl;
	mDrawable->SetScale(mScale, mScale);
	mDrawable->SetColor(mColor);
	//Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_PARTICLE, boost::lexical_cast<std::string>(mScale));
}

/*void Entity::Draw(sf::RenderTarget* target) const {
	// Set screen position.
	if(GetPositionType() == Entity::POSITIONTYPE_WORLD) {
		// Convert to world coordinates.
		Coordinates pos; //  = Root::get_mutable_instance().GetInputManagerPtr()->GetScreenCoordinates(mPosition.x, mPosition.y);
		pos.SetWorldFloat(mPosition);
		Vector2D worldPos = pos.GetWorldPixel();
		Root::get_mutable_instance().SetRenderMode(RENDERMODE_WORLD);
		mDrawable->SetPosition(worldPos.x, worldPos.y);
	} else if(GetPositionType() == Entity::POSITIONTYPE_SCREEN) {
		// Simply use screen coordinates.
		Root::get_mutable_instance().SetRenderMode(RENDERMODE_GUI);
		mDrawable->SetPosition(mPosition.x, mPosition.y);
	}

	mDrawable->SetRotation(- Vector2D::rad2Deg( mDirection.Rotation() ));

	target->Draw(*mDrawable);
}*/

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
