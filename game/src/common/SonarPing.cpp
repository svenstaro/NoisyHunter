#include "Root.hpp"
#include "SonarPing.hpp"

SonarPing::SonarPing(const Engine::Vector2D& pos, const Engine::Vector2D& direction, const float time_to_live, const float speed) {
	mPosition = pos;
	mDirection= direction;
	mTimeToLive = time_to_live;
	mUniqueId = 0;
	mSpeed = speed;
}

SonarPing::~SonarPing() {}

SonarPing* SonarPing::clone() const {
	return new SonarPing();
}

void SonarPing::Initialize() {
	boost::shared_ptr<sf::Shape> shape(new sf::Shape);
	*shape = sf::Shape::Circle(mPosition.x, mPosition.y, 10, sf::Color(122, 162, 255));
	mDrawable = shape;
}

void SonarPing::Update(const float time_delta) {
	mDirection.Normalize();
	mPosition += mDirection * mSpeed * time_delta;

	mTimeToLive -= time_delta;
	if(mTimeToLive <= 0) {
		mSpeed = 0;
	}

	UpdateAllAttachments(time_delta);

}

void SonarPing::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 SonarPing::GetEntityId() const {
	return ENTITYID_SONARPING;
}

void SonarPing::serialize(Engine::IOPacket& packet) {
	packet & mClientId;
	packet & mUniqueId;
	packet & mPosition.x;
	packet & mPosition.y;
	packet & mSpeed;
	packet & mTimeToLive;
	packet & mDirection.x;
	packet & mDirection.y;
}
