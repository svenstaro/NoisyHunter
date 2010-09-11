#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <boost/serialization/base_object.hpp>

#include "Vector2D.hpp"

namespace Engine {

class Entity {
public:

	enum Layer {
		LAYER_BACKGROUND = 1000,
		LAYER_WORLD = 1001,
		LAYER_REGULAR = 1002,
		LAYER_FOREGROUND = 1003
	};
	enum PositionType{
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

    void SetSpeed(const float x, const float y);
	void SetPosition(const float x, const float y);
	const Vector2D GetSpeed() const;
	const Vector2D GetPosition() const;
	Layer GetLayer() const;
    virtual PositionType GetPositionType() const;

	bool operator < (const Entity& other);


private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & mPosition.x;
        ar & mPosition.y;
        ar & mSpeed.x;
        ar & mSpeed.y;
        ar & mLayer;
	}

protected:
    Layer mLayer;

	Vector2D mPosition;
	Vector2D mSpeed;

	sf::Drawable* mDrawable;
};

}

#endif
