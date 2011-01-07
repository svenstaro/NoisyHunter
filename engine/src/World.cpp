#include <boost/foreach.hpp>
#include "World.hpp"
#include "Root.hpp"

namespace Engine {

World::World() {}

World::~World() {}

World* World::clone() const {}

void World::InitializePhysics() {
	mCollisionConfiguration = boost::shared_ptr<btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());
	mCollisionDispatcher = boost::shared_ptr<btCollisionDispatcher>(new btCollisionDispatcher(mCollisionConfiguration.get()));
	mBroadphase = boost::shared_ptr<btDbvtBroadphase>(new btDbvtBroadphase());
	mSimplex = boost::shared_ptr<btVoronoiSimplexSolver>(new btVoronoiSimplexSolver());
	mPdSolver = boost::shared_ptr<btMinkowskiPenetrationDepthSolver>(new btMinkowskiPenetrationDepthSolver());
	mSolver = boost::shared_ptr<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver());
	mDynamicsWorld = boost::shared_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(mCollisionDispatcher.get(), mBroadphase.get(), mSolver.get(), mCollisionConfiguration.get()));

	mConvexAlgo2d = boost::shared_ptr<btConvex2dConvex2dAlgorithm::CreateFunc>(new btConvex2dConvex2dAlgorithm::CreateFunc(mSimplex.get(), mPdSolver.get()));

	mCollisionDispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE, mConvexAlgo2d.get());
	mCollisionDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE, mConvexAlgo2d.get());
	mCollisionDispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE, mConvexAlgo2d.get());
	//mCollisionDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE, new btBox2dBox2dCollisionAlgorithm::CreateFunc());
	mCollisionDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE, mBox2dAlgo2d.get());
	mDynamicsWorld->setGravity(btVector3(0, 1, 0));

	if(!Root::get_const_instance().IsServer()) {
		mDebugDraw = boost::shared_ptr<DebugDraw>(new DebugDraw(Root::get_mutable_instance().GetRenderWindow()));
	//mDebugDraw.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		mDebugDraw->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

		mDynamicsWorld->setDebugDrawer(mDebugDraw.get());
	}
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
				mDynamicsWorld->removeRigidBody(entity.GetBody().get());
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
	if(!Root::get_const_instance().IsServer())
		mDynamicsWorld->debugDrawWorld();
}

void World::AddEntity(Entity* entity) {
	float pixels_per_meter = Root::get_const_instance().GetWorldPixelsPerFloat();
	float meters_per_pixel = (1.f/pixels_per_meter);

	mEntities.push_back(entity);
	mEntityListNeedsSorting = true;
	
	btTransform transform(btQuaternion(0, 0, 0, 1), btVector3(entity->GetPosition().x, entity->GetPosition().y, 0));
	boost::shared_ptr<btDefaultMotionState> motion_state(new btDefaultMotionState(transform));
	entity->SetMotionState(motion_state);
	btRigidBody::btRigidBodyConstructionInfo rb_info(0, motion_state.get(), entity->GetCollisionShape().get(), btVector3(0, 0, 0));
	boost::shared_ptr<btRigidBody> body(new btRigidBody(rb_info));
	body->setLinearFactor(btVector3(1,1,0));
	body->setAngularFactor(btVector3(0,0,1));
	entity->SetBody(body);

	mDynamicsWorld->addRigidBody(body.get());
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
	BOOST_FOREACH(Entity& entity, mEntities) {
		if(entity.GetClientId() == client_id) {
			mDynamicsWorld->removeRigidBody(entity.GetBody().get());
			mEntities.erase_if(boost::bind(&Entity::GetClientId, _1) == client_id);
		}
	}
}

void World::DeleteEntityByEntityUniqueId(const sf::Uint16 entity_unique_id) {
	BOOST_FOREACH(Entity& entity, mEntities) {
		if(entity.GetEntityUniqueId() == entity_unique_id) {
			mDynamicsWorld->removeRigidBody(entity.GetBody().get());
			mEntities.erase_if(boost::bind(&Entity::GetEntityUniqueId, _1) == entity_unique_id);
		}
	}
}

void World::OnLeaveGame() {}

sf::Uint16 World::GetEntityCount() const {
	return mEntities.size();
}

Entity& World::GetLastEntity() {
	return mEntities.back();
}

}
