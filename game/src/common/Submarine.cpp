#include "Submarine.hpp"

Submarine::Submarine(float pos_x, float pos_y) {
	mPosition = Engine::Vector2D(pos_x, pos_y);
	mLayer = Engine::Entity::LAYER_REGULAR;
	//mDrawable = mRoot.GetResourceManager().GetImage("submarine");
}

Submarine::~Submarine() {}

const Engine::Entity* Submarine::FireTorpedoTo(const Engine::Vector2D Pos) {
	// Calculate the Direction-Vector to the mouse position
	return new Torpedo(mPosition, mSpeed, Pos);
}

const Engine::Entity* Submarine::PingTo(const Engine::Vector2D Pos) {
	// Calculate the Cirection-Vector to the mouse position
	return new SonarPing();
}

