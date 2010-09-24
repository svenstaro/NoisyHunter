#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"

class Torpedo : public Engine::Entity {

public:
	Torpedo(const sf::Uint16 unique_id = 0, 
			const Engine::Vector2D& pos = Engine::Vector2D(0,0), 
			const Engine::Vector2D& speed = Engine::Vector2D(0,0), 
			const Engine::Vector2D& target_position = Engine::Vector2D(0,0));

	~Torpedo();

	void Update(const float time_delta);

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	void OnDeath();

	sf::Uint16 GetEntityId() const;

private:
  /*  friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
*/

	Engine::Vector2D mTargetPosition;
};

#endif
