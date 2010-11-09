#include "Root.hpp"
#include "WorldPolygon.hpp"

WorldPolygon::WorldPolygon() {
	mUniqueId = 0;
	mBorderWidth = 0.003;
	mTimeToLive = 1.f;
	mLifeTime = 0.f;
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

void WorldPolygon::SetBorderWidth(const float border_width) {
	mBorderWidth = border_width;
}

const float WorldPolygon::GetBorderWidth() {
	return mBorderWidth;
}

void WorldPolygon::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

sf::Uint16 WorldPolygon::GetEntityId() const {
	return ENTITYID_WORLDPOLYGON;
}

void WorldPolygon::serialize(Engine::IOPacket& packet) {
    packet & mUniqueId;
	packet & mPosition.x;
	packet & mPosition.y;
	packet & mBorderWidth;

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
		// Convert floats to pixels
		Engine::Coordinates c;
		c.SetWorldFloat(Engine::Vector2D(p.x, p.y));
		Engine::Vector2D p = c.GetWorldPixel();
		mShape.AddPoint(sf::Vector2f(p.x, p.y), sf::Color(64,128,255,50), sf::Color(100,140,255));
	}
	mShape.EnableFill(false);
	float out_width = mBorderWidth * Engine::Root::get_mutable_instance().GetWorldPixelsPerFloat();
	if (out_width < 1.f) out_width = 1.f;
	mShape.SetOutlineWidth(int(out_width));
	mShape.SetPosition(mPosition.x, mPosition.y);
}
