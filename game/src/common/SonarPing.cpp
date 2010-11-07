#include "Root.hpp"
#include "SonarPing.hpp"

SonarPing::SonarPing(const Engine::Vector2D& pos, const Engine::Vector2D& direction, const float time_to_live, const float speed) {
	mPosition = pos;
	mDirection= direction;
	mTimeToLive = time_to_live;
	mUniqueId = 0;
	mSpeed = speed;
}

SonarPing::~SonarPing() {}

SonarPing* SonarPing::clone() const {
	return new SonarPing();
}

void SonarPing::Initialize() {
	boost::shared_ptr<sf::Sprite> d(new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("sonarping")));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mSprite = *d;

	Engine::Vector2D position = Engine::Vector2D(0.f, 0.f);
	Engine::Vector2D direction = Engine::Vector2D(0.f, 1.f);
	// Creating particle system
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem();
	part_sys->SetPosition(position);
	part_sys->SetDirection(direction);
	part_sys->SetPositionType(Engine::Entity::PositionType::POSITIONTYPE_WORLDFLOAT);

	// Creating particle emitter
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter();
	part_emit->SetPosition(Engine::Vector2D(0.f, 0.f));
	part_emit->SetRotationOffset(0.f);
	part_emit->SetSpeed(0.f);
	part_emit->SetSpread(0.f);
	part_emit->SetTimeToLive(5.f);
	part_emit->SetRate(6.f);
	part_emit->SetStartScale(1.f);
	part_emit->SetEndScale(1.f);
	part_emit->SetBlendMode(sf::Blend::Alpha);
	part_emit->SetImageName("particle_sonarping");
	part_emit->SetStartAlpha(255.f);
	part_emit->SetEndAlpha(0.f);
	part_sys->AddEmitter(part_emit);

	Attach(*part_sys, Engine::Vector2D(0,0), 0, Engine::RestraintSettings(false,false,false));
}

void SonarPing::Update(const float time_delta) {
	mDirection.Normalize();
	mPosition += mDirection * mSpeed * time_delta;

	mTimeToLive -= time_delta;
	if(mTimeToLive <= 0) {
		mSpeed = 0;
	}

	UpdateAllAttachments(time_delta);

}

void SonarPing::Draw(sf::RenderTarget* target) const {
	Engine::Root::get_mutable_instance().SetRenderMode(Engine::RENDERMODE_WORLD);
	target->Draw(mSprite);

	DrawAllAttachments(target);
}

void SonarPing::OnCollide(const Engine::Entity& ent) {
}

sf::Uint16 SonarPing::GetEntityId() const {
	return ENTITYID_SONARPING;
}

void SonarPing::serialize(Engine::IOPacket& packet) {
	packet & mClientId;
	packet & mUniqueId;
	packet & mPosition.x;
	packet & mPosition.y;
	packet & mSpeed;
	packet & mTimeToLive;
	packet & mDirection.x;
	packet & mDirection.y;
}
