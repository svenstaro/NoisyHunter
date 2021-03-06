#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include "Vector2D.hpp"

namespace Engine {

// Structure holding screen and game coordinates.
class Coordinates {
public:
	void SetWorldPixel(const Vector2D coords);
	void SetWorldFloat(const Vector2D coords);
	void SetViewPixel(const Vector2D coords);
	void SetScreenPixel(const Vector2D coords);
	void SetScreenFloat(const Vector2D coords);

	const Vector2D GetWorldPixel() const;
	const Vector2D GetWorldFloat() const;
	const Vector2D GetViewPixel() const;
	const Vector2D GetScreenPixel() const;
	const Vector2D GetScreenFloat() const;

	static const Vector2D WorldFloatToWorldPixel(const Vector2D coords);
	static const Vector2D ScreenPixelToWorldFloat(const Vector2D coords);
	static const Vector2D WorldFloatToViewPixel(const Vector2D coords);

    static const float WorldFloatToWorldPixel(const float length);

private:
	Vector2D mWorldPixel;
};

}

#endif
