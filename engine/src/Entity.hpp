#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Vector2D.hpp"
#include "RestraintSettings.hpp"
#include "IOPacket.hpp"

namespace Engine {

// Forward declare EntityAttachment :(
class EntityAttachment;
class Entity {
public:
	enum PositionType {
		POSITIONTYPE_SCREENPIXEL,
		POSITIONTYPE_SCREENFLOAT,
		POSITIONTYPE_WORLDPIXEL,
		POSITIONTYPE_WORLDFLOAT,
		POSITIONTYPE_VIEWPIXEL
	};

	// Default constructor
	Entity();

	// Pure virtual destructor
	virtual ~Entity() = 0;

	// Virtual constructor (create)
	virtual Entity* create() const = 0;

	virtual void Initialize();

	virtual void GrabEntityUniqueId();
    
	// Callbacks
    virtual void OnCollide(const Entity& ent);
	// TODO: All the other callbacks
    
    // Performs some action on the entity. If validate is true, this 
    // will validate the action before actually performing it. 
    // Returns the response to be sent back or an empty packet if 
    // invalid or no response needed
    virtual sf::Packet PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate = false);

	virtual void Update(const float time_delta);

	virtual void UpdatePhysics(const float time_delta);

	void UpdateAllAttachments(const float time_delta);

	virtual void Draw(sf::RenderTarget* target) const;

	void DrawAllAttachments(sf::RenderTarget* target) const;

	virtual sf::Uint16 GetEntityTypeId() const = 0;

	sf::Uint16 GetEntityUniqueId() const;

	virtual void SetPosition(const float x, const float y);

	virtual void SetPosition(const Vector2D position);

	void SetSpeed(const float speed);

	void SetDirection(const Vector2D direction);

	const Vector2D GetPosition() const;

	float GetSpeed() const;

	const Vector2D GetDirection() const;

	int GetLayer() const;

    virtual PositionType GetPositionType() const;

	float GetTimeToLive() const;

	float GetLifeTime() const;

	void SetEntityUniqueId(const sf::Uint16 entity_unique_id);

	bool operator<(const Entity& other);

    virtual void serialize(IOPacket& packet);
    
    void SetClientId(const sf::Uint16 client_id);
    sf::Uint16 GetClientId() const;

	void Attach(Entity& entity,
				const Vector2D& position_offset,
				const float rotation_offset,
				RestraintSettings restraint_settings = RestraintSettings());

	void SetCollisionShape(const boost::shared_ptr<btCollisionShape> collision_shape); 

	boost::shared_ptr<btCollisionShape> GetCollisionShape();

	void SetBody(const boost::shared_ptr<btRigidBody> body);

	boost::shared_ptr<btRigidBody> GetBody();

	void SetMotionState(const boost::shared_ptr<btDefaultMotionState> motion_state);

	boost::shared_ptr<btDefaultMotionState> GetMotionState();

	static bool SortHelper(const Entity& l, const Entity& r);

protected:
	sf::Uint16 mClientId;
	sf::Uint16 mEntityUniqueId;

	Vector2D mPosition;
	float mSpeed;
	Vector2D mDirection;
	float mTimeToLive;
	float mLifeTime;

	int mLayer;

	boost::ptr_list<EntityAttachment> mAttachments;

	boost::shared_ptr<btCollisionShape> mCollisionShape;

	boost::shared_ptr<btRigidBody> mBody;

	boost::shared_ptr<btDefaultMotionState> mMotionState;

};

}

#endif
