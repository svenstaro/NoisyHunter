#ifndef CROSSHAIR_HPP
#define CROSSHAIR_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Vector2D.hpp"

class Crosshair : public Engine::Entity {
public:
    Crosshair(const sf::Uint16 unique_id = 0);

    ~Crosshair();

    void OnCollide(const Entity& ent);

	sf::Uint16 GetEntityId() const;
};

#endif
