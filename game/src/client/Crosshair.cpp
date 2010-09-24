#include "Crosshair.hpp"
#include "Root.hpp"

Crosshair::Crosshair(const sf::Uint16 unique_id) {
	mUniqueId = unique_id;
    mPosition = Engine::Vector2D(0.5, 0.5);
	mLayer = Engine::Entity::LAYER_FOREGROUND;
	sf::Sprite* d = new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("aim"));
	d->SetCenter(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
	mSpeed = Engine::Vector2D(0,0);
}

Crosshair::~Crosshair() {}

void Crosshair::OnCollide(const Entity& ent) {}

sf::Uint16 Crosshair::GetEntityId() const {
	return 5;
}
