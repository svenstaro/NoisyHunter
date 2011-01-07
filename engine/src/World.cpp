#include <boost/foreach.hpp>
#include "World.hpp"
#include "Root.hpp"

namespace Engine {

World::World() {}

World::~World() {}

World* World::clone() const {}

void World::InitializePhysics() {
	collisionConfiguration = boost::shared_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
	dispatcher = boost::shared_ptr<btCollisionDispatcher>(new btCollisionDispatcher(collisionConfiguration.get()));
	broadphase = boost::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
	simplex = boost::shared_ptr<btVoronoiSimplexSolver>(new btVoronoiSimplexSolver());
	pd_solver = boost::shared_ptr<btMinkowskiPenetrationDepthSolver>(new btMinkowskiPenetrationDepthSolver());
	solver = boost::shared_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver());
//	dynamicsWorld = boost::shared_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get()));
//	dynamicsWorld->setGravity(btVector3(0, 1, 0));

	mPixelsPerMeter = 64.f;
	mMetersPerPixel = (1.f/mPixelsPerMeter);

}

//void World::Initialize() {}

void World::Update(const float time_delta) {
	UpdateAllEntities(time_delta);
}

void World::UpdateAllEntities(const float time_delta) {
	BOOST_FOREACH(Entity& entity, mEntities) {
		entity.Update(time_delta);
		if(Root::get_mutable_instance().IsServer()) {
			if(entity.GetLifeTime() >= entity.GetTimeToLive()) {
				Root::get_mutable_instance().GetNetworkManagerPtr()->SendEntityDel(entity.GetEntityUniqueId(), mWorldUniqueId);
				mEntities.erase_if(boost::bind(&Entity::GetEntityUniqueId, _1) == entity.GetEntityUniqueId());
			}
		}
	}

	if(mEntityListNeedsSorting) {
		//mEntities.sort();
		mEntityListNeedsSorting = false;
	}
}

void World::AppendAllEntitiesToPacket() {
	BOOST_FOREACH(Entity& entity, mEntities) {
		Root::get_mutable_instance().GetNetworkManagerPtr()->
			AppendEntityToPacket(entity);
	}
}

void World::Draw(sf::RenderTarget* target) {

	Root::get_mutable_instance().SetRenderMode(RENDERMODE_WORLD);
	BOOST_FOREACH(Entity& entity, mEntities) {
		entity.Draw(target);
	}
}

void World::AddEntity(Entity* entity) {
	mEntities.push_back(entity);
	mEntityListNeedsSorting = true;

	// Physics stuff
	// just create a basic block as the collision_shape for debugging.
	
	boost::shared_ptr<btCollisionShape> shape(new btBoxShape(btVector3(btScalar(Root::get_const_instance().GetWindowSize().x / 2 * mMetersPerPixel), btScalar(0.2), btScalar(10))));
	entity->SetCollisionShape(shape);

	collisionShapes.push_back(entity->GetCollisionShape().get());
	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(Root::get_mutable_instance().GetWindowSize().x / 2 * mMetersPerPixel, Root::get_mutable_instance().GetWindowSize().y * mMetersPerPixel, 0));
	boost::shared_ptr<btDefaultMotionState> motion_state(new btDefaultMotionState(transform));
	btRigidBody::btRigidBodyConstructionInfo rb_info(0, motion_state.get(), entity->GetCollisionShape().get(), btVector3(0, 0, 0));
	boost::shared_ptr<btRigidBody> body(new btRigidBody(rb_info));
	body->setLinearFactor(btVector3(1,1,0));
	body->setAngularFactor(btVector3(0,0,1));

	//dynamicsWorld->addRigidBody(body.get());
}

void World::GrabWorldUniqueId() {
	mWorldUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

sf::Uint16 World::GetWorldUniqueId() {
	return mWorldUniqueId;
}

void World::SetWorldUniqueId(sf::Uint16 world_unique_id) {
	mWorldUniqueId = world_unique_id;
}

sf::Uint16 World::GetEntityCount() {
	return sf::Uint16(mEntities.size());
}

void World::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {}

Entity* World::GetEntityByEntityUniqueId(const sf::Uint16 entity_unique_id) {
   	BOOST_FOREACH(Entity& entity, mEntities) {
		if(entity.GetEntityUniqueId() == entity_unique_id) {
            return &entity;
        }
	} 
    return NULL;
}

void World::DeleteEntitiesByClientId(const sf::Uint16 client_id) {
	mEntities.erase_if(boost::bind(&Entity::GetClientId, _1) == client_id);
}

void World::DeleteEntityByEntityUniqueId(const sf::Uint16 entity_unique_id) {
	mEntities.erase_if(boost::bind(&Entity::GetEntityUniqueId, _1) == entity_unique_id);
}

void World::OnLeaveGame() {}

sf::Uint16 World::GetEntityCount() const {
	return mEntities.size();
}

Entity& World::GetLastEntity() {
	return mEntities.back();
}

}
