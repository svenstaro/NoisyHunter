#include "Root.hpp"
#include "Radar.hpp"

Radar::Radar() {}

Radar::~Radar() {}

Radar* Radar::create() const {
	return new Radar();
}

void Radar::Initialize() {
	boost::shared_ptr<sf::Sprite> d(new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("radar1")));
	d->SetColor(sf::Color(100,220,255));
	d->SetOrigin(0,d->GetSize().y);
	mDrawable = d;
	mDirection = Engine::Vector2D(1,0);
	mPosition = Engine::Vector2D(400,300);
}

void Radar::Update(const float time_delta) {
	mDirection.Normalize();
	mDirection.Rotate(-0.6*time_delta);

	UpdateAllAttachments(time_delta);
}

void Radar::OnCollide(const Engine::Entity& ent) {}

Engine::Entity::PositionType Radar::GetPositionType() const {
	return Engine::Entity::POSITIONTYPE_SCREENPIXEL;
}

sf::Uint16 Radar::GetEntityId() const {
	return ENTITYID_RADAR;
}
