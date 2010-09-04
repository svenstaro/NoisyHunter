#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Vector2D.hpp"

namespace Engine {

class Entity {
public:
	Entity();
	virtual ~Entity() = 0;

	virtual void OnCollide(const Entity& ent);

	virtual void Update(const float time_delta);

	void SetSpeed(const float x, const float y);
	void SetPosition(const float x, const float y);
	
	virtual void Draw(const sf::RenderTarget& target) const;

	const Vector2D GetSpeed() const;
	const Vector2D GetPosition() const;

	enum Layer {
		LAYER_BACKGROUND = 1000,
		LAYER_WORLD = 1001,
		LAYER_REGULAR = 1002,
		LAYER_GUI = 1003,
		LAYER_TOOLTIP = 1004
	}

	bool operator < (const Entity& other);
private:

	Vector2D mPosition;
	Vector2D mSpeed;

	sf::Drawable* mDrawable;
};

}

#endif
