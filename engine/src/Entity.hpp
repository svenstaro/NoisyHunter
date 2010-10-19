#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Vector2D.hpp"
#include "IOPacket.hpp"

namespace Engine {

class Entity {
public:
	enum Layer {
		LAYER_BACKGROUND = 1000,
		LAYER_WORLD = 1001,
		LAYER_REGULAR = 1002,
		LAYER_FOREGROUND = 1003
	};

	enum PositionType {
        POSITIONTYPE_SCREEN,
        POSITIONTYPE_WORLD
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

	virtual void Draw(sf::RenderTarget* target) const;

	virtual sf::Uint16 GetEntityId() const = 0;

	sf::Uint16 GetUniqueId() const;

    void SetSpeed(const float x, const float y);

	void SetPosition(const float x, const float y);

	const Vector2D GetSpeed() const;

	const Vector2D GetPosition() const;

	Layer GetLayer() const;

    virtual PositionType GetPositionType() const;

	bool operator<(const Entity& other);

    virtual void serialize(IOPacket& packet);
    
    void SetClientId(const sf::Uint16 client_id);
    sf::Uint16 GetClientId() const;

protected:
	sf::Uint16 mClientId;
	sf::Uint16 mUniqueId;

	Vector2D mPosition;
	Vector2D mSpeed;

    Layer mLayer;

	sf::Drawable* mDrawable;
};

}

#endif
