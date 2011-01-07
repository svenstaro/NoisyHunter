#ifndef BALL_HPP
#define BALL_HPP

#include "Entity.hpp"
#include "Coordinates.hpp"

class Ball : public Engine::Entity{
public:
    Ball();
    ~Ball();
    Ball* create() const;

    void Initialize(const Engine::Vector2D pos = Engine::Vector2D(0.5f, 0.5f), const Engine::Vector2D speed = Engine::Vector2D(0.5f,0.2f), float radius = 0.02f);

    void Update(float time_delta);
    void Draw(sf::RenderTarget *target) const;

    void OnCollide(const Engine::Entity& ent);

    sf::Uint16 GetEntityTypeId() const;

    void serialize(Engine::IOPacket& packet);

private:
    float mRadius;
    Engine::Vector2D mSpeedVector;
};

#endif
