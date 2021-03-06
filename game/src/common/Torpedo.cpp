#include "Root.hpp"
#include "Torpedo.hpp"

Torpedo::Torpedo(const Engine::Vector2D& pos,
				 const Engine::Vector2D& direction,
				 const float speed,
				 const Engine::Vector2D& target_position,
				 const float time_to_live) {
	mLayer = 900;
	SetPosition(pos);
	SetDirection(direction);
	SetSpeed(speed);
	mTargetPosition = target_position;
	mEntityUniqueId = 0;
	mReachedTargetAngle = false;
	mTimeToLive = time_to_live;
	mLifeTime = 0.f;
}

Torpedo::~Torpedo() {}

Torpedo* Torpedo::create() const {
	return new Torpedo();
}

void Torpedo::Initialize() {
	mSprite.SetImage(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("torpedo"));
	mSprite.SetOrigin(mSprite.GetSize().x / 2, mSprite.GetSize().y / 2);

	// Particle system for torpedo
	Engine::Vector2D position = Engine::Vector2D(0.f, 0.f);
	Engine::Vector2D direction = Engine::Vector2D(0.f, 0.f);
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem(position, direction, Engine::Entity::PositionType::POSITIONTYPE_WORLDFLOAT);
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter(Engine::Vector2D(0.f, 0.f), 0.f, 0.f, 20.f);
	part_emit->SetRate(5.f);
	part_emit->SetTimeToLive(5.f);
	part_emit->SetStartScale(0.7f);
	part_emit->SetEndScale(3.f);
	part_emit->SetStartAlpha(200.f);
	part_emit->SetEndAlpha(0);
	part_emit->SetImageName("torpedo_trail");
	part_emit->SetEndColor(sf::Color(0, 0, 0));
	part_sys->AddEmitter(part_emit);

	Attach(*part_sys, Engine::Vector2D(0,0), 0, Engine::RestraintSettings(false, false, false));

	mCollisionShape = boost::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(btScalar(0.01), btScalar(0.01), btScalar(0.01))));
}

void Torpedo::Update(const float time_delta) {
	Engine::Vector2D relative_target = mTargetPosition - mPosition;
	relative_target.Normalize();
	mBody->applyTorqueImpulse(btVector3(0,0,90));
	mBody->applyCentralForce(btVector3(relative_target.x,relative_target.y,0));

	/*
	if (!mReachedTargetAngle) {
		float angle = relative_target.Rotation() - mDirection.Rotation();

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

		mDirection.Rotate(angle);
	}

	mDirection.Normalize();
	mPosition += mDirection * mSpeed * time_delta;
*/
	if(mTimeToLive >= 0) {
		mLifeTime += time_delta;
	}

	UpdatePhysics(time_delta);
	Engine::Vector2D p = Engine::Coordinates::WorldFloatToWorldPixel(mPosition);
	mSprite.SetPosition(p.x, p.y);
	UpdateAllAttachments(time_delta);
}

void Torpedo::Draw(sf::RenderTarget* target) const {
	target->Draw(mSprite);
	DrawAllAttachments(target);
}

void Torpedo::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

void Torpedo::OnDeath() {
	// TODO: Do stuff
}

sf::Uint16 Torpedo::GetEntityTypeId() const {
	return ENTITYTYPEID_TORPEDO;
}

void Torpedo::SetTargetPosition(const Engine::Vector2D target_position) {
	mTargetPosition = target_position;
}

void Torpedo::SetTimeToLive(const float time_to_live) {
	mTimeToLive = time_to_live;
}

/*template<class Archive>
void Torpedo::serialize(Archive & ar, const unsigned int version) {

    //ar & boost::serialization::base_object<Engine::Entity>(*this);

    ar & mTargetPosition.x;
    ar & mTargetPosition.y;
}*/

void Torpedo::serialize(Engine::IOPacket& packet) {
	packet & mClientId;
	packet & mEntityUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
	packet & mSpeed;
	packet & mDirection.x;
	packet & mDirection.y;
    packet & mTargetPosition.x;
    packet & mTargetPosition.y;
}
