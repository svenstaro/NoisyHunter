#include "Coordinates.hpp"
#include "Root.hpp"

#include <iostream>


namespace Engine {

// SETTER

void Coordinates::SetWorldPixel(const Vector2D coords) {
	mWorldPixel = coords;
}
void Coordinates::SetWorldFloat(const Vector2D coords) {
	mWorldPixel = coords * Root::get_const_instance().GetWorldPixelsPerFloat();
}
void Coordinates::SetViewPixel(const Vector2D coords) {
	const sf::View& view = Root::get_const_instance().GetWorldView();
	mWorldPixel = coords + Vector2D(view.GetCenter().x - view.GetSize().x / 2.f, view.GetCenter().y - view.GetSize().y / 2.f); // coords + View Offset
}
void Coordinates::SetScreenPixel(const Vector2D coords) {
	const sf::View& view = Root::get_const_instance().GetWorldView();
	SetViewPixel(coords - Vector2D(view.GetViewport().Left, view.GetViewport().Top)); // coords - ViewPORT Offset
}
void Coordinates::SetScreenFloat(const Vector2D coords) {
	SetScreenPixel(Vector2D(coords.x * Root::get_const_instance().GetWindowSize().x, coords.y * Root::get_const_instance().GetWindowSize().y));
}

// GETTER

const Vector2D Coordinates::GetWorldPixel() const {
	return mWorldPixel;
}
const Vector2D Coordinates::GetWorldFloat() const {
	return mWorldPixel / Root::get_const_instance().GetWorldPixelsPerFloat();
}
const Vector2D Coordinates::GetViewPixel() const {
	const sf::View& view = Root::get_const_instance().GetWorldView();
	return mWorldPixel - Vector2D(view.GetCenter().x - view.GetSize().x / 2.f, view.GetCenter().y - view.GetSize().y / 2.f); // mWorldPixel - View Offset
}
const Vector2D Coordinates::GetScreenPixel() const {
	const sf::View& view = Root::get_const_instance().GetWorldView();
	return GetViewPixel() + Vector2D(view.GetViewport().Left, view.GetViewport().Top); // ViewPixel + ViewPORT Offset
}
const Vector2D Coordinates::GetScreenFloat() const {
	return Vector2D(GetScreenPixel().x / Root::get_const_instance().GetWindowSize().x, GetScreenPixel().y / Root::get_const_instance().GetWindowSize().y);
}


// STATIC CONVERSTION FUNCTIONS
const Vector2D Coordinates::WorldFloatToWorldPixel(const Vector2D coords) {
	Coordinates tmp;
	tmp.SetWorldFloat(coords);
	return tmp.GetWorldPixel();
}

const Vector2D Coordinates::ScreenPixelToWorldFloat(const Vector2D coords) {
	Coordinates tmp;
	tmp.SetScreenPixel(coords);
	return tmp.GetWorldFloat();
}
const Vector2D Coordinates::WorldFloatToViewPixel(const Vector2D coords) {
	Coordinates tmp;
	tmp.SetWorldFloat(coords);
	return tmp.GetViewPixel();
}

const float Coordinates::WorldFloatToWorldPixel(const float length) {
    Ćoordinates tmp;
    tmp.SetWorldFloat(new Coordinates(length, 0));
    return tmp.GetWorldPixel().x;
}

}
