#include "WorldPolygon.hpp"

WorldPolygon::WorldPolygon(const sf::Uint16 unique_id) {
	mUniqueId = unique_id;
}

WorldPolygon::~WorldPolygon() {}

void WorldPolygon::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 WorldPolygon::GetEntityId() const {
	return 4;
}
