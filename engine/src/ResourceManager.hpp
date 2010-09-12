#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ImageMagick/Magick++.h>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

//#include "Root.hpp"

namespace Engine {

class ResourceManager {
public:
    ResourceManager();
    //ResourceManager(Root* root);
    ~ResourceManager();

    bool AddImage(const boost::filesystem::path& path, const std::string& imgname,
        const sf::Uint16 width, const sf::Uint16 height, const std::string& key="");
    const sf::Image& GetImage(const std::string& img);

    void AddFont(sf::Font& font, std::string key);
    const sf::Font& GetFont(const std::string& key);
private:
	boost::ptr_map<std::string, sf::Image> mImages;
	boost::ptr_map<std::string, sf::Font> mFonts;
};

}

#endif
