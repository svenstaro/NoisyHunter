#include "Crosshair.hpp"
#include "Root.hpp"

Crosshair::Crosshair(){
    mPosition = Engine::Vector2D(0.5, 0.5);
	mLayer = Engine::Entity::LAYER_TOOLTIP;
	sf::Sprite* d = new sf::Sprite(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("aim"));
	d->SetCenter(d->GetSize().x / 2, d->GetSize().y / 2);
	mDrawable = d;
	mSpeed = Engine::Vector2D(0,0);
}

Crosshair::~Crosshair() {}


void Crosshair::OnCollide(const Entity& ent) {}
