#include "Root.hpp"
#include "SonarPing.hpp"

SonarPing::SonarPing(const float direction_angle) {
	mDirectionAngle = direction_angle;
	mUniqueId = 0;
}

SonarPing::~SonarPing() {}

SonarPing* SonarPing::clone() const {
	return new SonarPing();
}

void SonarPing::Initialize() {
	// TODO: Get own image here!
}

void SonarPing::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 SonarPing::GetEntityId() const {
	return ENTITYID_SONARPING;
}
