#ifndef WORLD_HPP
#define WORLD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>
#include <boost/signals2.hpp>

#include <bullet/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h>
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#include <BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "DebugDraw.hpp"

namespace Engine {

void worldTickCallback(btDynamicsWorld *world, btScalar timeStep);

class World {
public:
	World();
	virtual ~World() = 0;
	virtual World* clone() const = 0;

	void InitializePhysics();
	virtual void Initialize() = 0;
	virtual void Update(const float time_delta);
	virtual void AppendAllEntitiesToPacket();
	void Draw(sf::RenderTarget* const target);
	void AddEntity(Entity* entity);
	
	void GrabWorldUniqueId();
	sf::Uint16 GetWorldUniqueId();
	void SetWorldUniqueId(sf::Uint16 world_unique_id);
	virtual sf::Uint16 GetWorldTypeId() const = 0;
	virtual sf::Uint16 GetEntityCount();
	
	// This isn't pure virtual because no client world needs to handle interactions.
	virtual void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

	Entity* GetEntityByEntityUniqueId(const sf::Uint16 entity_unique_id);
	template <typename T>
			std::vector<T*> GetAllEntitiesByType() {

		std::vector<T*> entities;

		T t;
		sf::Uint16 entity_type_id = t.GetEntityTypeId();

		BOOST_FOREACH(Entity& entity, mEntities) {
			if(entity.GetEntityTypeId() == entity_type_id) {
				entities.push_back( (T*)&entity );
			}
		}
		return entities;

	}

	void DeleteEntitiesByClientId(const sf::Uint16 client_id);
	void DeleteEntityByEntityUniqueId(const sf::Uint16 entity_unique_id);
	virtual void OnLeaveGame();
	sf::Uint16 GetEntityCount() const;
	Entity& GetLastEntity();

	void TickCallback(btScalar timestep);

protected:
	void UpdateAllEntities(const float time_delta);	sf::Uint16 mWorldUniqueId;

	boost::ptr_vector<Entity> mEntities;
	boost::shared_ptr<btDefaultCollisionConfiguration> mCollisionConfiguration;
	boost::shared_ptr<btCollisionDispatcher> mCollisionDispatcher;
	boost::shared_ptr<btDbvtBroadphase> mBroadphase;
	boost::shared_ptr<btVoronoiSimplexSolver> mSimplex;
	boost::shared_ptr<btMinkowskiPenetrationDepthSolver> mPdSolver;
	boost::shared_ptr<btSequentialImpulseConstraintSolver> mSolver;
	boost::shared_ptr<btDiscreteDynamicsWorld> mDynamicsWorld;
	boost::shared_ptr<btConvex2dConvex2dAlgorithm::CreateFunc> mConvexAlgo2d;
	boost::shared_ptr<btBox2dBox2dCollisionAlgorithm::CreateFunc> mBox2dAlgo2d;

	boost::shared_ptr<DebugDraw> mDebugDraw;

	bool mEntityListNeedsSorting;

};

}

#endif
