#include "Root.hpp"
#include "WorldPolygon.hpp"

WorldPolygon::WorldPolygon() {
	mUniqueId = 0;
}

WorldPolygon::~WorldPolygon() {}

WorldPolygon* WorldPolygon::clone() const {
	return new WorldPolygon();
}

void WorldPolygon::Draw(sf::RenderTarget* target) const {
	target->Draw(mShape);
}

void WorldPolygon::Initialize() {
	RebuildShape();
}

void WorldPolygon::AddPoint(const sf::Vector2f point) {
	mPoints.push_back(point);
	RebuildShape();
}

void WorldPolygon::ClearAllPoints() {
	mPoints.clear();
	RebuildShape();
}

void WorldPolygon::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

sf::Uint16 WorldPolygon::GetEntityId() const {
	return 4;
}

void WorldPolygon::serialize(Engine::IOPacket& packet) {
    packet & mUniqueId;
	packet & mPosition.x;
	packet & mPosition.y;

	if (packet.IsStreamOut()) {
		// Stream data from packet to list
		ClearAllPoints();
		sf::Uint16 n;
		packet & n;
		for (int i = 0; i < n; i++) {
			sf::Vector2f p;
			packet & p.x;
			packet & p.y;
			AddPoint(p);
		}
	} else {
		// Stream data from list to packet
		sf::Uint16 n = int(mPoints.size());
		packet & n;
		BOOST_FOREACH(sf::Vector2f& p, mPoints) {
			packet & p.x;
			packet & p.y;
		}
	}
}


void WorldPolygon::RebuildShape() {
	mShape = sf::Shape();
	BOOST_FOREACH(sf::Vector2f& p, mPoints) {
		mShape.AddPoint(p, sf::Color(64,128,255,50), sf::Color(0,64,255));
	}
	mShape.EnableFill(true);
	mShape.SetOutlineWidth(3);
	mShape.SetPosition(mPosition.x, mPosition.y);
}
