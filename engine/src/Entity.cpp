#include "Entity.hpp"

namespace Engine {

    Entity::Entity() {}
    Entity::~Entity() {}

	bool Entity::operator < (const Entity& other){
		return mLayer < other.GetLayer();
	}


	template<class Archive>
    void Entity::serialize(Archive & ar, const unsigned int version){
        ar & mPosition.x;
        ar & mPosition.y;
        ar & mSpeed.x;
        ar & mSpeed.y;
        ar & (sf::Uint16)mLayer;
    }


	void Entity::Update(const float time_delta) {
		mPosition += mSpeed * time_delta;
	}

	void Entity::Draw(sf::RenderTarget* target) const {
		mDrawable->SetPosition(mPosition.x, mPosition.y);
		mDrawable->SetRotation(Vector2D::rad2Deg(mSpeed.Rotation()));
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




