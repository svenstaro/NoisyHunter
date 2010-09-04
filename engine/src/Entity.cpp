#include "Entity.hpp"

namespace Engine {

	bool Entity::operator < (const Entity& other){
		return mLayer < other.GetLayer();
	}
	
	void Entitiy::Update(const float time_delta) {
		mPosition += mSpeed * time_delta;
	}

	void Entity::Draw(const sf::RenderTarget& target) const {
		mDrawable->SetPosition(mPosition.x, mPosition.y);
		mDrawable->SetRotation(Vector2D::rad2Deg(mSpeed.Rotation()));
		target.Draw(*mDrawable);
	}

}
