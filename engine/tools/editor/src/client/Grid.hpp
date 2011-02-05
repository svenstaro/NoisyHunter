#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "EntityTypeId.hpp"
#include "IOPacket.hpp"
#include "Vector2D.hpp"

class Grid : public Engine::Entity {
public:
	Grid();

	~Grid();

	Grid* create() const;

	void Initialize();

    void Update(float time_delta);
	void Draw(sf::RenderTarget *target) const;

	sf::Uint16 GetEntityTypeId() const;

	void serialize(Engine::IOPacket& packet);
};

#endif
