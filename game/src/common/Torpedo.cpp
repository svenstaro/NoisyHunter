#include "Root.hpp"
#include "Torpedo.hpp"

Torpedo::Torpedo(const Engine::Vector2D& pos,
				 const Engine::Vector2D& speed,
				 const Engine::Vector2D& target_position,
				 const float time_to_live) {
	mPosition = pos;
	mSpeed = speed;
	mTargetPosition = target_position;
	mUniqueId = 0;
	mReachedTargetAngle = false;
	mTimeToLive = time_to_live;
}

Torpedo::~Torpedo() {}

Torpedo* Torpedo::clone() const {
	return new Torpedo();
}

void Torpedo::Initialize() {
	sf::Sprite* d = new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("torpedo"));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
}

void Torpedo::Update(const float time_delta) {
	Engine::Vector2D relative_target = mTargetPosition - mPosition;

	if (!mReachedTargetAngle) {
		float angle = relative_target.Rotation() - mSpeed.Rotation();

		if(Engine::Vector2D::rad2Deg(angle) > 180)
			angle -= Engine::Vector2D::deg2Rad(360);
		else if(Engine::Vector2D::rad2Deg(angle) < -180)
			angle += Engine::Vector2D::deg2Rad(360);

		float max_angle = 2 * time_delta;
		if(angle > max_angle)
			angle = max_angle;
		else if(angle < -max_angle)
			angle = -max_angle;
		else
			mReachedTargetAngle = true;

		mSpeed.Rotate(angle);
	}

	mPosition += mSpeed * time_delta;

	mTimeToLive -= time_delta;

	if (mTimeToLive <= 0) {
		// TODO: explode, yeah!
		mSpeed = Engine::Vector2D(0,0);
	}
}


void Torpedo::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

void Torpedo::OnDeath() {
	// TODO: Do stuff
}

sf::Uint16 Torpedo::GetEntityId() const {
	return 3;
}

/*template<class Archive>
void Torpedo::serialize(Archive & ar, const unsigned int version) {

    //ar & boost::serialization::base_object<Engine::Entity>(*this);

    ar & mTargetPosition.x;
    ar & mTargetPosition.y;
}*/

void Torpedo::serialize(Engine::IOPacket& packet) {
	packet & mClientId;
	packet & mUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
    packet & mSpeed.x;
    packet & mSpeed.y;
    packet & mTargetPosition.x;
    packet & mTargetPosition.y;
}
