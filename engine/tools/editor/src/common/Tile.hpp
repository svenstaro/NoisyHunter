#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "EntityTypeId.hpp"
#include "IOPacket.hpp"
#include "Vector2D.hpp"

class Tile : public Engine::Entity {
public:
	Tile();
	~Tile();

	Tile* create() const;

	void Initialize(const std::string& image = "",
					const float x = 0,
					const float y = 0);

	void Update(float time_delta);
	void Draw(sf::RenderTarget *target) const;

	sf::Uint16 GetEntityTypeId() const;

	void serialize(Engine::IOPacket &packet);

	void SetImage(const std::string& image);
	void SetColor(sf::Color color);

private:
	std::string mTileset;
	int mTile;
	sf::Color mColor;
	std::string mImageKey;
	Engine::Vector2D mOffset;
};

#endif
