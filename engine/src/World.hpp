#ifndef WORLD_HPP
#define WORLD_HPP

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h"
#include <boost/signals2.hpp>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

namespace Engine {

class World {
public:
	World();
	virtual ~World() = 0;
	virtual World* clone() const = 0;

	void InitializePhysics();
	virtual void Initialize() = 0;
	virtual void Update(const float time_delta);
	void AppendAllEntitiesToPacket();
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

protected:
	void UpdateAllEntities(const float time_delta);	sf::Uint16 mWorldUniqueId;

	boost::ptr_vector<Entity> mEntities;
	boost::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
	boost::shared_ptr<btCollisionDispatcher> dispatcher;
	boost::shared_ptr<btDbvtBroadphase> broadphase;
	boost::shared_ptr<btVoronoiSimplexSolver> simplex;
	boost::shared_ptr<btMinkowskiPenetrationDepthSolver> pd_solver;
	boost::shared_ptr<btSequentialImpulseConstraintSolver> solver;
	boost::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	float mPixelsPerMeter;
	float mMetersPerPixel;

	bool mEntityListNeedsSorting;

};

}

#endif
