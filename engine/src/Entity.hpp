#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <boost/ptr_container/ptr_list.hpp>

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
	enum Layer {
		LAYER_BACKGROUND = 1000,
		LAYER_WORLD = 1001,
		LAYER_REGULAR = 1002,
		LAYER_FOREGROUND = 1003
	};

	enum PositionType {
		POSITIONTYPE_SCREENPIXEL,
		POSITIONTYPE_WORLDPIXEL,
		POSITIONTYPE_WORLDFLOAT,
		POSITIONTYPE_VIEWPIXEL
	};

	// Default constructor
	Entity();

	// Virtual destructor
	virtual ~Entity() = 0;

	// Virtual constructor (clone)
	virtual Entity* clone() const = 0;

	virtual void Initialize();

	virtual void GrabUniqueId();
    
	// Callbacks
    virtual void OnCollide(const Entity& ent);
	// TODO: All the other callbacks
    
    // Performs some action on the entity. If validate is true, this 
    // will validate the action before actually performing it. 
    // Returns the response to be sent back or an empty packet if 
    // invalid or no response needed
    virtual sf::Packet PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate = false);

	virtual void Update(const float time_delta);

	void UpdateAllAttachments(const float time_delta);

	virtual void Draw(sf::RenderTarget* target) const;

	void DrawAllAttachments(sf::RenderTarget* target) const;

	virtual sf::Uint16 GetEntityId() const = 0;

	sf::Uint16 GetUniqueId() const;

	void SetPosition(const float x, const float y);

	void SetPosition(const Vector2D position);

	void SetSpeed(const float speed);

	void SetDirection(const Vector2D direction);

	const Vector2D GetPosition() const;

	const float GetSpeed() const;

	const Vector2D GetDirection() const;

	Layer GetLayer() const;

    virtual PositionType GetPositionType() const;

	bool operator<(const Entity& other);

    virtual void serialize(IOPacket& packet);
    
    void SetClientId(const sf::Uint16 client_id);
    sf::Uint16 GetClientId() const;

	void Attach(Entity& entity,
				const Vector2D& position_offset,
				const float rotation_offset,
				RestraintSettings restraint_settings = RestraintSettings());
protected:
	sf::Uint16 mClientId;
	sf::Uint16 mUniqueId;

	Vector2D mPosition;
	float mSpeed;
	Vector2D mDirection;

    Layer mLayer;

	sf::Drawable* mDrawable;

	boost::ptr_list<EntityAttachment> mAttachments;
};

}

#endif
