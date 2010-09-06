#include "Entity.hpp"
#include "Root.hpp"

#include <iostream>

namespace Engine {

    Entity::Entity() {
		mDrawable = &sf::Sprite(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("default"));
	}
    Entity::~Entity() {}

	bool Entity::operator < (const Entity& other){
		return mLayer < other.GetLayer();
	}

	void Entity::Update(const float time_delta) {
		mPosition += mSpeed * time_delta;
	}

	void Entity::Draw(sf::RenderTarget* target) const {
		mDrawable->SetPosition(mPosition.x, mPosition.y);
		float rotation = 0;
		if (mSpeed.x != 0 && mSpeed.y != 0) rotation = mSpeed.Rotation();
		mDrawable->SetRotation(Vector2D::rad2Deg(rotation));

		target->Draw(*mDrawable);
	}


    void Entity::SetSpeed(const float x, const float y) {
        mSpeed = Vector2D(x, y);
    }
	void Entity::SetPosition(const float x, const float y) {
        mPosition = Vector2D(x, y);
	}
	const Vector2D Entity::GetSpeed() const {
        return mSpeed;
	}
	const Vector2D Entity::GetPosition() const {
        return mPosition;
	}






	Entity::Layer Entity::GetLayer() const {
        return mLayer;
    }



}




