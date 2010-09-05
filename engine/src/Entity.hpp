#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Vector2D.hpp"

namespace Engine {

class Entity {
public:

	enum Layer {
		LAYER_BACKGROUND = 1000,
		LAYER_WORLD = 1001,
		LAYER_REGULAR = 1002,
		LAYER_GUI = 1003,
		LAYER_TOOLTIP = 1004
	};


	Entity();
	virtual ~Entity() = 0;

	// callbacks
	virtual void OnCollide(const Entity& ent) = 0;
	// TODO: All the other callbacks

	virtual void Update(const float time_delta);
	virtual void Draw(sf::RenderTarget* target) const;

    void SetSpeed(const float x, const float y);
	void SetPosition(const float x, const float y);
	const Vector2D GetSpeed() const;
	const Vector2D GetPosition() const;
	Layer GetLayer() const;

	bool operator < (const Entity& other);

	friend sf::Packet& operator<<(sf::Packet& Packet, const Entitiy& ent);
	friend sf::Packet& operator>>(sf::Packet& Packet, Entitiy& ent);
	
protected:
    Layer mLayer;

	Vector2D mPosition;
	Vector2D mSpeed;

	sf::Drawable* mDrawable;
};

}

#endif
