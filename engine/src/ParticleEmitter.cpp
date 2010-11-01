#include <boost/bind.hpp>

#include "ParticleEmitter.hpp"

namespace Engine {

ParticleEmitter::ParticleEmitter(const Vector2D& position_offset,
								 const float rotation_offset,
								 const float speed,
								 const float spread,
								 const float time_to_live,
								 const float rate,
								 const sf::Blend::Mode mode,
								 const sf::Color& start_color,
								 const sf::Color& end_color,
								 const float start_alpha,
								 const float end_alpha,
								 const float start_scale,
								 const float end_scale,
								 const std::string& image_name) {
	mPositionOffset = position_offset;
	mRotationOffset = rotation_offset;
	mSpeed = speed;
	mSpread = spread;
	mTimeToLive = time_to_live;
	mRate = rate;

	mStartColor = start_color;
	mEndColor = end_color;

	mStartAlpha = start_alpha;
	mEndAlpha = end_alpha;

	mStartScale = start_scale;
	mEndScale = end_scale;

	mImageName = image_name;
}

ParticleEmitter::~ParticleEmitter() {}

ParticleEmitter* ParticleEmitter::clone() const {
	return new ParticleEmitter();
}

void ParticleEmitter::Initialize(const Vector2D& position_of_partsys,
								 const Vector2D& direction_of_partsys,
								 const PositionType pos_type_of_partsys) {
	mPosition = mPositionOffset + position_of_partsys;
	mDirection = direction_of_partsys;
	mDirection.Rotate(mRotationOffset);
	mPositionType = pos_type_of_partsys;
	mTimeSinceLastParticle = 0.f;
}

void ParticleEmitter::Update(const float time_delta,
							 const Vector2D& position_of_partsys,
							 const Vector2D& direction_of_partsys) {
	mPosition = mPositionOffset + position_of_partsys;
	mDirection = direction_of_partsys;
	mDirection.Rotate(mRotationOffset);
	// The following line does the job of the commented code, nice!
	mParticles.erase_if(boost::bind(&Particle::GetLifeTime, _1) >= mTimeToLive);

	mTimeSinceLastParticle += time_delta;
	// Rate is amount of particles sent per second and time_delta is secs.
	
	while(
		  mTimeSinceLastParticle >= 1.f / mRate) {
		float spread = sf::Randomizer::Random(-mSpread/2, mSpread/2);
		Vector2D spread_vector = mDirection;
		spread_vector.Normalize();
		spread_vector.Rotate(Vector2D::deg2Rad(spread));
		Particle* particle = new Particle(mPosition, spread_vector, mSpeed, mStartColor, mEndColor, mStartAlpha, mEndAlpha, mStartScale, mEndScale, mTimeToLive, mBlendMode, mImageName, mPositionType);
		particle->Initialize();
		mParticles.push_back(particle);
		mTimeSinceLastParticle -= 1.f / mRate;
	}


	BOOST_FOREACH(Particle& particle, mParticles)
		particle.Update(time_delta);

	UpdateAllAttachments(time_delta);
}

void ParticleEmitter::Draw(sf::RenderTarget* target) const {
	BOOST_FOREACH(const Particle& particle, mParticles)
		particle.Draw(target);
	DrawAllAttachments(target);
}

void ParticleEmitter::SetPositionOffset(const Vector2D& position_offset) {
	mPositionOffset = position_offset;
}

void ParticleEmitter::SetRotationOffset(const float position_offset) {
	mRotationOffset = position_offset;
}

void ParticleEmitter::SetSpeed(const float speed) {
	mSpeed = speed;
}

void ParticleEmitter::SetSpread(const float spread) {
	mSpread = spread;
}

void ParticleEmitter::SetTimeToLive(const float ttl) {
	mTimeToLive = ttl;
}

void ParticleEmitter::SetRate(const float rate) {
	mRate = rate;
}

void ParticleEmitter::SetBlendMode(const sf::Blend::Mode mode) {
	mBlendMode = mode;

}

void ParticleEmitter::SetStartColor(const sf::Color& start_color) {
	mStartColor = start_color;
}

void ParticleEmitter::SetEndColor(const sf::Color& end_color) {
	mEndColor = end_color;
}

void ParticleEmitter::SetStartAlpha(const float start_alpha) {
	mStartAlpha = start_alpha;
}

void ParticleEmitter::SetEndAlpha(const float end_alpha) {
	mEndAlpha = end_alpha;
}

void ParticleEmitter::SetStartScale(const float start_scale) {
	mStartScale = start_scale;
}

void ParticleEmitter::SetEndScale(const float end_scale) {
	mEndScale = end_scale;
}

void ParticleEmitter::SetImageName(const std::string image_name) {
	mImageName = image_name;
}

const Vector2D& ParticleEmitter::GetPositionOffset() const {
	return mPositionOffset;
}

const float ParticleEmitter::GetRotationOffset() const {
	return mRotationOffset;
}

const float ParticleEmitter::GetSpeed() const {
	return mSpeed;
}

const float ParticleEmitter::GetSpread() const {
	return mSpread;
}

const float ParticleEmitter::GetTimeToLive() const {
	return mTimeToLive;
}

const float ParticleEmitter::GetRate() const {
	return mRate;
}

const sf::Blend::Mode ParticleEmitter::GetBlendMode() const {
	return mBlendMode;
}

const sf::Color& ParticleEmitter::GetStartColor() const {
	return mStartColor;
}

const sf::Color& ParticleEmitter::GetEndColor() const {
	return mEndColor;
}

const float ParticleEmitter::GetStartAlpha() const {
	return mStartAlpha;
}

const float ParticleEmitter::GetEndAlpha() const {
	return mEndAlpha;
}

const float ParticleEmitter::GetStartScale() const {
	return mStartScale;
}

const float ParticleEmitter::GetEndScale() const {
	return mEndScale;
}

sf::Uint16 ParticleEmitter::GetEntityId() const {
	return 50002;
}

Entity::PositionType ParticleEmitter::GetPositionType() const {
	return mPositionType;
}

}
