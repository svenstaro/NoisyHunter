#include <SFML/Graphics.hpp>

#include "Grid.hpp"
#include "Root.hpp"

Grid::Grid() {
	mLayer = 0;
	SetPosition(Engine::Vector2D(0, 0));
	mEntityUniqueId = 0;
}

Grid::~Grid() {}

Grid* Grid::create() const {
	return new Grid();
}

void Grid::Initialize() {}

void Grid::Update(float time_delta) {}

void Grid::Draw(sf::RenderTarget *target) const {
	Engine::Root& root = Engine::Root::get_mutable_instance();

	root.SetRenderMode(Engine::RENDERMODE_WORLD);

	Engine::Vector2D top_left = Engine::Coordinates::ScreenPixelToWorldFloat(Engine::Vector2D(0,0));
	Engine::Vector2D bottom_right = Engine::Coordinates::ScreenPixelToWorldFloat(
			root.GetWindowSize());
	sf::Color c(255, 255, 255, 60);
	for(int i = ceil(top_left.x); i < bottom_right.x; ++i) {
		target->Draw(sf::Shape::Line(i*root.GetWorldPixelsPerFloat(), 0,
									 i*root.GetWorldPixelsPerFloat(), root.GetWindowSize().y,
									 1, c));
		sf::Text t(boost::lexical_cast<std::string>(i));
		t.SetCharacterSize(12);
		t.SetPosition(round((i+0.5)*root.GetWorldPixelsPerFloat()-t.GetRect().Width/2), 10);
		target->Draw(t);
	}
	for(int i = ceil(top_left.y); i < bottom_right.y; ++i) {
		target->Draw(sf::Shape::Line(0, i*root.GetWorldPixelsPerFloat(),
									 root.GetWindowSize().x, i*root.GetWorldPixelsPerFloat(),
									 1, c));
		if(i != 0) {
			sf::Text t(boost::lexical_cast<std::string>(i));
			t.SetCharacterSize(12);
			t.SetPosition(10, round((i+0.5)*root.GetWorldPixelsPerFloat()-t.GetRect().Height/2));
			target->Draw(t);
		}
	}
}

sf::Uint16 Grid::GetEntityTypeId() const {
	return 0;
}

void Grid::serialize(Engine::IOPacket& packet) {}
