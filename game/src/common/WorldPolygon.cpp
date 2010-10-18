#include "Root.hpp"
#include "WorldPolygon.hpp"

WorldPolygon::WorldPolygon() {
	mUniqueId = 0;
}

WorldPolygon::~WorldPolygon() {}

void WorldPolygon::Initialize() {
	// TODO: Get own image here!
}

void WorldPolygon::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

sf::Uint16 WorldPolygon::GetEntityId() const {
	return 4;
}
