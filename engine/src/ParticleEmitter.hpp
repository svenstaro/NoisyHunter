#ifndef PARTICLEEMITTER_HPP 
#define PARTICLEEMITTER_HPP

#include <boost/ptr_container/ptr_list.hpp>

#include "Entity.hpp"
#include "Particle.hpp"

namespace Engine {

class ParticleEmitter : public Entity {
public:
	ParticleEmitter();
	
	~ParticleEmitter();

	ParticleEmitter* clone() const;
	
	void Initialize();

    void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

private:
	boost::ptr_list<Particle> mParticles;

	PositionType mPositionType;
};

}

#endif
