#include "Root.hpp"
#include "Radar.hpp"

Radar::Radar() {}

Radar::~Radar() {}

Radar* Radar::create() const {
	return new Radar();
}

void Radar::Initialize() {

	mRay.SetImage(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("radar1"));
	mRay.SetColor(sf::Color(60,255,100));
	mRay.SetOrigin(mRay.GetSize().x, mRay.GetSize().y);
	mRay.SetPosition(400,300);

	mBackground.SetImage(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("radar_background"));
	mBackground.SetColor(sf::Color(60,255,100));
	mBackground.SetOrigin(mBackground.GetSize().x / 2, mBackground.GetSize().y / 2);
	mBackground.SetPosition(400,300);

	mDirection = Engine::Vector2D(1,0);
}

void Radar::Update(const float time_delta) {
	mDirection.Normalize();
	mDirection.Rotate(0.8 * time_delta);
	mRay.SetRotation(- Engine::Vector2D::rad2Deg( mDirection.Rotation() ));

	UpdateAllAttachments(time_delta);
}

void Radar::Draw(sf::RenderTarget* target) const {
	target->Draw(mBackground);
	target->Draw(mRay);
}

void Radar::OnCollide(const Engine::Entity& ent) {}

Engine::Entity::PositionType Radar::GetPositionType() const {
	return Engine::Entity::POSITIONTYPE_SCREENPIXEL;
}

sf::Uint16 Radar::GetEntityTypeId() const {
	return ENTITYTYPEID_RADAR;
}
