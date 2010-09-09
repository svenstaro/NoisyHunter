#include "Submarine.hpp"

#include "Root.hpp"
#include <SFML/Graphics.hpp>

Submarine::Submarine(float pos_x, float pos_y) {
	mPosition = Engine::Vector2D(pos_x, pos_y);
	mLayer = Engine::Entity::LAYER_REGULAR;
	sf::Sprite* d = new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("submarine"));
	d->SetCenter(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
	mSpeed = Engine::Vector2D(0.1,0);
}

Submarine::~Submarine() {}


void Submarine::Update(float time_delta){
    Engine::Vector2D relative_target = mTarget - mPosition;
    float angle = relative_target.Rotation() - mSpeed.Rotation();

    if ( Engine::Vector2D::rad2Deg(angle) > 180 ) angle -= Engine::Vector2D::deg2Rad(360);
    else if ( Engine::Vector2D::rad2Deg(angle) < -180 ) angle += Engine::Vector2D::deg2Rad(360);

	float max_angle = 2 * time_delta;
	if (angle > max_angle) {
		angle = max_angle;
	} else if (angle < -max_angle) {
		angle = -max_angle;
	}

    mSpeed.Rotate(angle);
    mPosition += mSpeed * time_delta;
}


const Engine::Entity* Submarine::FireTorpedoTo(const Engine::Vector2D Pos) {
	// Calculate the Direction-Vector to the mouse position
	return new Torpedo(mPosition, mSpeed, Pos);
}

const Engine::Entity* Submarine::PingTo(const Engine::Vector2D Pos) {
	// Send a Ping into direction of pos vector
	Engine::Vector2D diff = Pos - mPosition;
	return new SonarPing(diff.Rotation());
}



void Submarine::OnCollide(const Engine::Entity& ent){

}
void Submarine::OnDamage(const float dmg){

}
void Submarine::OnFire(){

}


void Submarine::SetTarget(const Engine::Vector2D target) {
    mTarget = target;
}

