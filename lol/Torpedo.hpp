#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"

class Torpedo : public Engine::Entity {

public:
	Torpedo();
	Torpedo(Engine::Vector2D pos, Engine::Vector2D speed, Engine::Vector2D target_position);
	~Torpedo();

	// callbacks

	void Update(const float time_delta);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);


	Engine::Vector2D mTargetPosition;
};

#endif
