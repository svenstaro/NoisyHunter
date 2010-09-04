#include "Submarine.hpp"
#include "Root.hpp"

Submarine::Submarine(float pos_x, float pos_y) {
	mPosition = Engine::Vector2D(pos_x, pos_y);
	mDrawable = mRoot.GetResourceManager().GetImage("submarine");
}
	
const Engine::Entity& Submarine::FireTorpedoTo(const Engine::Vector2D Pos) {
	// Calculate the Direction-Vector to the mouse position
	Torpedo tp = Torpedo(mPosition, mSpeed, Pos);
	return Torpedo;
}

void Submarine::PingTo(ENgine::Vector2D Pos) {
	// Calculate the Cirection-Vector to the mouse position
}

