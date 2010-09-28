#include "SonarPing.hpp"

SonarPing::SonarPing(const sf::Uint16 unique_id,
					 const float direction_angle) {
	mUniqueId = unique_id;
	mDirectionAngle = direction_angle;
}

SonarPing::~SonarPing() {}

void SonarPing::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 SonarPing::GetEntityId() const {
	return 1;
}
