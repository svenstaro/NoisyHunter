#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include "Entity.hpp"

class Submarine : Engine::Entity {
public:
    Submarine();

    // callbacks
    void OnCollide(const Engine::Entity& ent);
    void OnDamage(const float dmg);
    void OnFire();

private:

};

#endif
