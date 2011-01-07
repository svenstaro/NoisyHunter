#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "World.hpp"
#include "Ball.hpp"

class GameWorld : public Engine::World {
public:
    GameWorld();
    ~GameWorld();
    GameWorld* clone() const;

    void Initialize();
    void Update(float time_diff);
    void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    void OnPressUp();
    void OnPressDown();

    sf::Uint16 GetWorldTypeId() const;
};

#endif
