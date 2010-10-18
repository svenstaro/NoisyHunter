#include "Root.hpp"
#include "SonarPing.hpp"

SonarPing::SonarPing(const float direction_angle) {
	mDirectionAngle = direction_angle;
	mUniqueId = 0;
}

SonarPing::~SonarPing() {}

void SonarPing::Initialize() {
	// TODO: Get own image here!
}

void SonarPing::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 SonarPing::GetEntityId() const {
	return 1;
}
