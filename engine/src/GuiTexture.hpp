#ifndef GUITEXTURE_HPP
#define GUITEXTURE_HPP

#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>

#include <SFML/Graphics.hpp>

#include "Logger.hpp"

namespace Engine {

namespace GuiTextureElementStateType {
	enum GuiTextureElementStateType {
		SPRITE = 1,
		TILED = 2
	};
}

struct GuiTextureElementState {
public:
	GuiTextureElementStateType::GuiTextureElementStateType Type;
	sf::FloatRect Subrect;
};

struct GuiTextureElement {
public:
	std::map<std::string, int> States;
	sf::Image* Image;
};

class GuiTexture {
public:
	GuiTexture();
	sf::Sprite GetTextureForKey(const std::string& key) const;
	const std::string& GetName() const;

	static void LoadLayoutFile(const std::string& filename);
private:
	std::string mName;
	std::map<std::string, GuiTextureElement> mElements;
};

}

#endif // GUITEXTURE_HPP
