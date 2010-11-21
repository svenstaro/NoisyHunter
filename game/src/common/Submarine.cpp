#include <SFML/Graphics.hpp>

#include "Submarine.hpp"
#include "Root.hpp"
#include "NetworkCommand.hpp"

Submarine::Submarine(const float pos_x,
					 const float pos_y,
					 const sf::Uint16 client_id) {
	mLayer = Engine::Entity::LAYER_REGULAR;
	SetPosition(Engine::Vector2D(pos_x, pos_y));
	SetTarget(mPosition);
	SetSpeed(0.f);
	SetDirection(Engine::Vector2D(1,0));
	mClientId = client_id;
	mUniqueId = 0;
	mTimeToLive = 1.f;
	mLifeTime = 0.f;
}

Submarine::~Submarine() {}

Submarine* Submarine::create() const {
	return new Submarine();
}

void Submarine::Initialize() {
	boost::shared_ptr<sf::Sprite> d(new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("submarine")));
	d->SetOrigin(d->GetSize().x / 2, d->GetSize().y / 2);
	mSprite = *d;

	mTargetMarkerRotation = 0;

	// Particle system for submarine
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem();
	part_sys->SetPosition(Engine::Vector2D(0.f, 0.f));
	part_sys->SetDirection(Engine::Vector2D(0.f, -1.2f));
	part_sys->SetPositionType(Engine::Entity::PositionType::POSITIONTYPE_WORLDFLOAT);
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter();
	part_emit->SetPosition(Engine::Vector2D(0.f, 0.f));
	part_emit->SetRotationOffset(0.f);
	part_emit->SetSpeed(0.06f);
	part_emit->SetSpread(20.f);
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
	float dist = relative_target.Magnitude();
	if(dist > 0.01) {
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
	if(flip_x) {
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

	mTargetMarkerRotation += time_delta * 100;

	UpdateAllAttachments(time_delta);
}

void Submarine::Draw(sf::RenderTarget* target) const {
	Engine::Root::get_mutable_instance().SetRenderMode(Engine::RENDERMODE_WORLD);
	target->Draw(mSprite);

	if(mClientId == Engine::Root::get_mutable_instance().GetClientId()) {
		// Draw the target marker
		sf::Sprite target_marker(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("submarine_target"));
		Engine::Vector2D target_marker_pos = Engine::Coordinates::WorldFloatToWorldPixel(mTarget);
		target_marker.SetPosition(target_marker_pos.x, target_marker_pos.y);
		target_marker.SetOrigin(target_marker.GetSize().x / 2, target_marker.GetSize().y / 2);
		target_marker.Rotate(mTargetMarkerRotation);
		target->Draw(target_marker);
	}

	DrawAllAttachments(target);
}

const Engine::Entity* Submarine::FireTorpedoTo(const Engine::Vector2D target_pos, const float time_to_live) {
	mDirection.Normalize();
	Torpedo* torpedo = new Torpedo();
	torpedo->SetPosition(mPosition);
	torpedo->SetDirection(mDirection);
	torpedo->SetSpeed(0.036 * 3); // speed of submarine * 3
	torpedo->SetTargetPosition(target_pos);
	torpedo->SetTimeToLive(time_to_live);

	return torpedo;
}

const Engine::Entity* Submarine::FireSonarPing(const Engine::Vector2D direction, const float time_to_live) {
	Engine::Vector2D dir = direction - mPosition;
	dir.Normalize();
	SonarPing* sonarping = new SonarPing();
	sonarping->SetPosition(mPosition);
	sonarping->SetDirection(dir);
	sonarping->SetTimeToLive(time_to_live);
	sonarping->SetSpeed(0.036 * 3); // speed of submarine * 3
	return sonarping;
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
	return ENTITYID_SUBMARINE;
}

void Submarine::SetTarget(const float x, const float y) {
	SetTarget(Engine::Vector2D(x,y));
}

void Submarine::SetTarget(const Engine::Vector2D target) {
    mTarget = target;
	SetSpeed(0.036);
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
