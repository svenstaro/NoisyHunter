#include <SFML/Graphics.hpp>
#include "SvgParser.hpp"

int main() {
	sf::RenderWindow RenderWin(sf::VideoMode(800, 600, 32), "SvgParser");

	while(RenderWin.IsOpened()) {
	RenderWin.Clear(sf::Color(sf::Color::Blue));

	SvgParser parser;

	sf::Shape shape = parser.ParseFromFile("testlevel.svg");
	shape.EnableFill(false);
	shape.EnableOutline(true);
	shape.SetOutlineWidth(5.f);
	shape.SetPointOutlineColor(2, sf::Color::Green);

	RenderWin.Draw(shape);

	RenderWin.Display();
	}
}
