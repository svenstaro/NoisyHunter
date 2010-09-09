#ifndef CROSSHAIR_HPP
#define CROSSHAIR_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Vector2D.hpp"

class Crosshair : public Engine::Entity {
public:
    Crosshair();
    ~Crosshair();

    void OnCollide(const Entity& ent);
};


#endif
