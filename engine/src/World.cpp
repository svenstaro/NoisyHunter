#include <boost/foreach.hpp>
#include "World.hpp"
#include "Root.hpp"

namespace Engine {

World::World() {}

World::~World() {}

void World::InitializePhysics() {
	collisionConfiguration = boost::shared_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
	dispatcher = boost::shared_ptr<btCollisionDispatcher>(new btCollisionDispatcher(collisionConfiguration.get()));
	broadphase = boost::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
	simplex = boost::shared_ptr<btVoronoiSimplexSolver>(new btVoronoiSimplexSolver());
	pd_solver = boost::shared_ptr<btMinkowskiPenetrationDepthSolver>(new btMinkowskiPenetrationDepthSolver());
	solver = boost::shared_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver());
	dynamicsWorld = boost::shared_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(dispatcher.get(),broadphase.get(),solver.get(),collisionConfiguration.get()));
	dynamicsWorld->setGravity(btVector3(0, 1, 0));
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
				Root::get_mutable_instance().GetNetworkManagerPtr()->SendEntityDel(entity.GetEntityUniqueId());
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
			AppendEntityToPacket(entity, mWorldUniqueId);
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
}

void World::GrabWorldUniqueId() {
	mWorldUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

sf::Uint16 World::GetWorldUniqueId() {
	return mWorldUniqueId;
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


}

