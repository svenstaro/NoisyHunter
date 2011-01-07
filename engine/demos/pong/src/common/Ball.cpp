#include "Ball.hpp";

Ball::Ball() {}
Ball::~Ball() {}
Ball* Ball::create() const{
    return new Ball();
}

void Ball::Initialize(const Engine::Vector2D pos, const Engine::Vector2D speed, float radius) {
    mPosition = pos;
    mSpeedVector = speed;
    mRadius = radius;
}

void Ball::Update(float time_delta) {
    mPosition += mSpeedVector * time_delta;
}

void Ball::Draw(sf::RenderTarget *target) const {
    Engine::Vector2D p = Engine::Coordinates::WorldFloatToWorldPixel(mPosition);
    sf::Shape shape = sf::Shape::Circle(p.x, p.y, Engine::Coordinates::WorldFloatToWorldPixel(mRadius), sf::Color::White, 1.f, sf::Color::White);
    shape.EnableOutline(true);
    shape.EnableFill(false);
    target->Draw(shape);
}

void Ball::OnCollide(const Engine::Entity& ent) {}

sf::Uint16 Ball::GetEntityTypeId() const {
    return 0x0100;
}

void Ball::serialize(Engine::IOPacket& packet) {
    packet & mEntityUniqueId;
    packet & mPosition.x;
    packet & mPosition.y;
    packet & mSpeedVector.x;
    packet & mSpeedVector.y;
    packet & mRadius;
}


