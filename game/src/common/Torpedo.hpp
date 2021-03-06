#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entity.hpp"
#include "EntityTypeId.hpp"
#include "Vector2D.hpp"
#include "IOPacket.hpp"
#include "ParticleSystem.hpp"

class Torpedo : public Engine::Entity {

public:
	Torpedo(const Engine::Vector2D& pos = Engine::Vector2D(0,0),
			const Engine::Vector2D& direction = Engine::Vector2D(1,0),
			const float speed = 0.3f,
			const Engine::Vector2D& target_position = Engine::Vector2D(0,0),
			const float time_to_live = 3.f);

	~Torpedo();

	Torpedo* create() const;

	void Initialize();

	void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	void OnDeath();

	sf::Uint16 GetEntityTypeId() const;

    void serialize(Engine::IOPacket& packet);
	void SetTargetPosition(const Engine::Vector2D target_position);
	void SetTimeToLive(const float time_to_live);

private:
	sf::Sprite mSprite;
  /*  friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
*/
	bool mReachedTargetAngle;
	Engine::Vector2D mTargetPosition;
};

#endif
