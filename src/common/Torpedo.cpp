#include "Torpedo.hpp"

Torpedo::Torpedo() {
	mPosition = Engine::Vector2D(0, 0);
	mTargetPosition = Engine::Vector2D(0, 0);
	mSpeed = Engine::Vector2D(0, 0);
	//mDrawable = mRoot.GetResourceManager().GetImage("torpedo");

	mLayer = Engine::Entity::LAYER_REGULAR;
}

Torpedo::Torpedo(Engine::Vector2D pos, Engine::Vector2D speed, Engine::Vector2D target_position) {
	mPosition = pos;
	mSpeed = speed;
	mTargetPosition = target_position;
}

void Torpedo::Update(const float time_delta) {
	Engine::Vector2D relative_target = mTargetPosition - mPosition;
	float angle = Engine::Vector2D::Angle(mSpeed, relative_target);
	float max_angle = 1 * time_delta;
	if (angle > max_angle) {
		angle = max_angle;
	} else if (angle < -max_angle) {
		angle = -max_angle;
	}
	mSpeed.Rotate(angle);

	mPosition += mSpeed * time_delta;
}
