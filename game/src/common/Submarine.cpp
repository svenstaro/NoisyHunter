#include <SFML/Graphics.hpp>

#include "Submarine.hpp"
#include "Root.hpp"
#include "NetworkCommand.hpp"

Submarine::Submarine(const float pos_x,
					 const float pos_y,
					 const sf::Uint16 client_id) {
	mLayer = Engine::Entity::LAYER_REGULAR;
	SetPosition(Engine::Vector2D(pos_x, pos_y));
	SetSpeed(0.06);
	SetDirection(Engine::Vector2D(1,0));
	mClientId = client_id;
	mUniqueId = 0;
}

Submarine::~Submarine() {}

Submarine* Submarine::clone() const {
	return new Submarine();
}

void Submarine::Initialize() {
	sf::Sprite* d = new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("submarine"));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mSprite = *d;


	// Particle system for submarine
	Engine::Vector2D position = Engine::Vector2D(0.f, 0.f);
	Engine::Vector2D direction = Engine::Vector2D(0.f, -1.2f);
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem(position, direction, Engine::Entity::PositionType::POSITIONTYPE_WORLDFLOAT);
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter(Engine::Vector2D(0.f, 0.f), 0.f, 0.1f, 20.f);
	part_emit->SetRate(1.7f);
	part_emit->SetTimeToLive(5.f);
	part_emit->SetStartScale(0.5f);
	part_emit->SetEndScale(2.f);
	part_emit->SetStartAlpha(180);
	part_emit->SetEndAlpha(0);
	part_emit->SetImageName("particle_bubble");
	part_emit->SetEndColor(sf::Color(0,0,255));
	part_sys->AddEmitter(part_emit);

	Attach(*part_sys, Engine::Vector2D(0,0), 0, Engine::RestraintSettings(false,false,true));
}

void Submarine::Update(float time_delta) {
    Engine::Vector2D relative_target = mTarget - mPosition;
	if (relative_target.Magnitude() > 0.01){
		float angle = relative_target.Rotation() - mDirection.Rotation();

		if(Engine::Vector2D::rad2Deg(angle) > 180)
			angle -= Engine::Vector2D::deg2Rad(360);
		else if(Engine::Vector2D::rad2Deg(angle) < -180)
			angle += Engine::Vector2D::deg2Rad(360);

		float max_angle = 0.5 * time_delta;
		if(angle > max_angle)
			angle = max_angle;
		else if(angle < -max_angle)
			angle = -max_angle;

		mDirection.Rotate(angle);
		mDirection.Normalize();
		mPosition += mDirection * mSpeed * time_delta;
	}


	// Convert to world coordinates.
	Engine::Coordinates pos;
	pos.SetWorldFloat(mPosition);
	Engine::Vector2D worldPos = pos.GetWorldPixel();
	mSprite.SetPosition(sf::Vector2f(worldPos.x, worldPos.y));

	float rot = Engine::Vector2D::rad2Deg( mDirection.Rotation());
	bool flip_x = rot > 90 || rot < -90;
	mSprite.FlipX(flip_x);
	if (flip_x) {
		if (rot > 90) rot = 180 - rot;
		if (rot < -90) rot = - 180 - rot;
		if (rot > 30) rot = 30;
		if (rot < -30) rot = -30;
		mSprite.SetRotation( rot );
	} else {
		if (rot > 30) rot = 30;
		if (rot < -30) rot = -30;
		mSprite.SetRotation(- rot );
	}


	UpdateAllAttachments(time_delta);
}

void Submarine::Draw(sf::RenderTarget* target) const {

	Engine::Root::get_mutable_instance().SetRenderMode(Engine::RENDERMODE_WORLD);
	target->Draw(mSprite);

	DrawAllAttachments(target);
}

const Engine::Entity* Submarine::FireTorpedoTo(const Engine::Vector2D Pos, const float time_to_live) {
	mDirection.Normalize();
	return new Torpedo(mPosition, mDirection, mSpeed * 3, Pos, time_to_live);
}

const Engine::Entity* Submarine::PingTo(const Engine::Vector2D Pos) {
	// Send a Ping into direction of pos vector
	Engine::Vector2D diff = Pos - mPosition;
	return new SonarPing(diff.Rotation());
}

void Submarine::OnCollide(const Engine::Entity& ent) {
	// TODO: Do stuff
}

void Submarine::OnDamage(const float dmg) {
	// TODO: Do stuff
}

void Submarine::OnFire() {
	// TODO: Do stuff
}

sf::Packet Submarine::PerformAction(const sf::Uint16 action_id, sf::Packet& packet, const bool validate) {
    sf::Packet default_response;
    default_response << sf::Uint16(Engine::NETCMD_ENTITYACTION) << action_id;
    
    if(action_id == 0x01) {
        // Set Target
        sf::Uint16 x;
        sf::Uint16 y;
        packet >> x >> y;
        if(validate) {
            // TODO: Validation
            // on fail: return sf::Packet();
        }
        SetTarget(Engine::Vector2D(x,y));
		Engine::Root::get_mutable_instance().GetLogManagerPtr()->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_ENTITY, "Performed action.");
        default_response << x << y;
        return default_response;
    }
    return sf::Packet();
    
}

sf::Uint16 Submarine::GetEntityId() const {
	return 2;
}

void Submarine::SetTarget(const float x, const float y) {
	SetTarget(Engine::Vector2D(x,y));
}

void Submarine::SetTarget(const Engine::Vector2D target) {
    mTarget = target;
	SetSpeed(0.06);
}

void Submarine::serialize(Engine::IOPacket& packet) {
    packet & mUniqueId;
    packet & mClientId;
    packet & mPosition.x;
	packet & mPosition.y;
	packet & mSpeed;
	packet & mDirection.x;
	packet & mDirection.y;
    packet & mTarget.x;
	packet & mTarget.y;
}
