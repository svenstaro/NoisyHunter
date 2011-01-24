#include <iostream>

#include "Entity.hpp"
#include "Root.hpp"
#include "EntityAttachment.hpp"

namespace Engine {

Entity::Entity() {}

Entity::~Entity() {}

void Entity::Initialize() {}

void Entity::GrabEntityUniqueId() {
	mEntityUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

void Entity::OnCollide(const Entity& ent) {}

bool Entity::operator<(const Entity& other) {
	return mLayer < other.GetLayer();
}

void Entity::serialize(IOPacket& packet) {
	packet & mClientId;
    packet & mEntityUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
	packet & mSpeed;
	packet & mDirection.x;
	packet & mDirection.y;
}

sf::Packet Entity::PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate) {
    // Do not perform any action by default and return that nothing was
    // done at all.
    return sf::Packet();
}

void Entity::Update(const float time_delta) {
	mPosition += mSpeed * time_delta;
}

void Entity::UpdatePhysics(float time_delta) {
	btTransform trans;
	mBody->getMotionState()->getWorldTransform(trans);
	btVector3 origin = trans.getOrigin();
	SetPosition(Vector2D(origin.x(), origin.y()));

	btMatrix3x3 rot;
	rot.setIdentity();
	rot = trans.getBasis();
	float fx,fy,fz;
	rot.getEulerZYX(fz,fy,fx);
	mDirection = Vector2D(1,0);
	mDirection.Rotate( (PI-fz) / 180.0 * PI );
}

void Entity::UpdateAllAttachments(const float time_delta) {
	// Update EntityAttachments.
	BOOST_FOREACH(EntityAttachment attachment, mAttachments)
		attachment.Update(time_delta, mPosition, mDirection);
}

void Entity::Draw(sf::RenderTarget* target) const {
	DrawAllAttachments(target);
}

void Entity::DrawAllAttachments(sf::RenderTarget* target) const {
	// Update EntityAttachments.
	BOOST_FOREACH(EntityAttachment attachment, mAttachments)
		attachment.Draw(target);
}

void Entity::SetPosition(const float x, const float y) {
	SetPosition(Vector2D(x, y));
}

void Entity::SetPosition(const Vector2D position) {
	mPosition = position;
	if(mBody != NULL) {
		btTransform trans;
		mBody->getMotionState()->getWorldTransform(trans);
		trans.setOrigin(btVector3(position.x,position.y,0.f));
	}
}

void Entity::SetSpeed(const float speed) {
	mSpeed = speed;
}

void Entity::SetDirection(const Vector2D direction) {
	mDirection = direction;
	mDirection.Normalize();
}

const Vector2D Entity::GetPosition() const {
	return mPosition;
}

float Entity::GetSpeed() const {
	return mSpeed;
}

const Vector2D Entity::GetDirection() const {
	return mDirection;
}

int Entity::GetLayer() const {
	return mLayer;
}

Entity::PositionType Entity::GetPositionType() const {
	return Entity::POSITIONTYPE_WORLDFLOAT;
}

float Entity::GetTimeToLive() const {
	return mTimeToLive;
}

float Entity::GetLifeTime() const {
	return mLifeTime;
}

sf::Uint16 Entity::GetEntityUniqueId() const {
	return mEntityUniqueId;
}

void Entity::SetEntityUniqueId(const sf::Uint16 entity_unique_id) {
	mEntityUniqueId = entity_unique_id;
}

void Entity::SetClientId(const sf::Uint16 client_id) {
    mClientId = client_id;
}

sf::Uint16 Entity::GetClientId() const {
    return mClientId;
}

void Entity::Attach(Entity& entity,
					const Vector2D& position_offset,
					const float rotation_offset,
					RestraintSettings restraint_settings) {
	EntityAttachment* attachment = new EntityAttachment(&entity, mPosition, mDirection, position_offset, rotation_offset, restraint_settings);
	//EntityAttachment* attachment = new EntityAttachment(&entity);
	mAttachments.push_back(attachment);
}

boost::shared_ptr<btRigidBody> mBody;
void Entity::SetCollisionShape(const boost::shared_ptr<btCollisionShape> collision_shape) {
	mCollisionShape = collision_shape;
}

boost::shared_ptr<btCollisionShape> Entity::GetCollisionShape() {
	return mCollisionShape;
}

void Entity::SetBody(const boost::shared_ptr<btRigidBody> body) {
	mBody = body;
}

boost::shared_ptr<btRigidBody> Entity::GetBody() {
	return mBody;
}

void Entity::SetMotionState(const boost::shared_ptr<btDefaultMotionState> motion_state) {
	mMotionState = motion_state;
}

boost::shared_ptr<btDefaultMotionState> Entity::GetMotionState() {
	return mMotionState;
}

bool Entity::SortHelper(const Entity& l, const Entity& r) {
	return l.GetLayer() < r.GetLayer();
}

}
