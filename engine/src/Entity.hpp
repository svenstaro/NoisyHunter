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

	Entity();

	virtual ~Entity() = 0;

	// callbacks
	virtual void OnCollide(const Entity& ent);
	// TODO: All the other callbacks

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

protected:
	sf::Uint16 mUniqueId;

	Vector2D mPosition;
	Vector2D mSpeed;

    Layer mLayer;

	sf::Drawable* mDrawable;
};

}

#endif
