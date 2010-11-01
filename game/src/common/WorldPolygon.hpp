#ifndef WORLDPOLYGON_HPP
#define WORLDPOLYGON_HPP

#include <list>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Entity.hpp"
#include "Coordinates.hpp"

class WorldPolygon : public Engine::Entity {
public:
	WorldPolygon();

	~WorldPolygon();

	WorldPolygon* clone() const;

	void Draw(sf::RenderTarget* target) const;

	void Initialize();

	void AddPoint(const sf::Vector2f point);
	void ClearAllPoints();

	void SetBorderWidth(const float border_width);
	const float GetBorderWidth();

	// callbacks
	void OnCollide(const Engine::Entity& ent);

	sf::Uint16 GetEntityId() const;

	void serialize(Engine::IOPacket& packet);

private:
	void RebuildShape();

	sf::Vector2f mOrigin;
	std::list<sf::Vector2f> mPoints;	// world float coordinates
	float mBorderWidth;					// world float coordinates
	sf::Shape mShape;
};

#endif
