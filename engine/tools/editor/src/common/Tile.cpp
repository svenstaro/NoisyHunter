#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "Root.hpp"
#include "NetworkCommand.hpp"

Tile::Tile() {
	mLayer = 1000;
	mEntityUniqueId = 0;
	mOffset = Engine::Vector2D(0, 0);
}

Tile::~Tile() {}

Tile* Tile::create() const {
	return new Tile();
}

void Tile::Initialize(const std::string& image,
					  const float x,
					  const float y) {
	SetPosition(x, y);
	SetImage(image);

	GrabEntityUniqueId();
}

void Tile::Update(float time_delta) {}

void Tile::Draw(sf::RenderTarget* target) const {
	Engine::Root::get_mutable_instance().SetRenderMode(Engine::RENDERMODE_WORLD);
	float size = Engine::Root::get_mutable_instance().GetWorldPixelsPerFloat();
	if(mImageKey != "") {
		sf::Sprite s(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetImage(mImageKey));
		Engine::Vector2D pos = Engine::Coordinates::WorldFloatToWorldPixel(mPosition);
		s.SetPosition(pos.x, pos.y);
		s.SetSubRect(sf::IntRect(size*mOffset.x, size*mOffset.y, size, size));
		target->Draw(s);
	} else {
		Engine::Vector2D pos = Engine::Coordinates::WorldFloatToWorldPixel(mPosition);
		sf::Shape s = sf::Shape::Rectangle(pos.x, pos.y, size, size, mColor);
		target->Draw(s);
	}
}

sf::Uint16 Tile::GetEntityTypeId() const {
	return ENTITYTYPEID_TILE;
}

void Tile::serialize(Engine::IOPacket &packet) {
	packet & mEntityUniqueId;
	packet & mPosition.x;
	packet & mPosition.y;
	packet & mOffset.x;
	packet & mOffset.y;
	packet & mColor.r & mColor.g & mColor.b & mColor.a;
	packet & mImageKey;
}

void Tile::SetImage(const std::string& image) {
	mImageKey = image;
}

void Tile::SetColor(sf::Color color) {
	mColor = color;
}
