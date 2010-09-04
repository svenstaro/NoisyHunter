#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <ImageMagick/Magick++.h>

#include <boost/ptr_map.hpp>
#include <boost/lexical_cast.hpp>

namespace Engine {

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    bool AddImage(const boost::filesystem::path& path, const std::string& imgname,
        const sf::Uint16 width, const sf::Uint16 height, const std::string& key="");
    const sf::Image& GetImage(const std::string& img) const;

private:
	boost::ptr_map<std::string, sf::Image> mImages;
};

}

#endif
