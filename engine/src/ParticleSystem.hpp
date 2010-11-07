#ifndef PARTICLESYSTEM_HPP 
#define PARTICLESYSTEM_HPP

#include <boost/ptr_container/ptr_list.hpp>

#include "Entity.hpp"
#include "ParticleEmitter.hpp"

namespace Engine {

class ParticleSystem : public Entity {
public:
	ParticleSystem(const Vector2D& position = Vector2D(0.f, 0.f),
				   const Vector2D& direction = Vector2D(0.f, 0.f),
				   const PositionType pos_type = Entity::PositionType::POSITIONTYPE_WORLDFLOAT);
	
	~ParticleSystem();

	ParticleSystem* clone() const;
	
	void Initialize();

    void Update(const float time_delta);

	void Draw(sf::RenderTarget* target) const;

	sf::Uint16 GetEntityId() const;

	Entity::PositionType GetPositionType() const;

	void AddEmitter(ParticleEmitter* emitter);

	void SetPosition(const Vector2D& position);
	void SetDirection(const Vector2D& direction);
	void SetPositionType(const PositionType pos_type);
private:
	boost::ptr_list<ParticleEmitter> mParticleEmitters;

	PositionType mPositionType;
};

}

#endif
