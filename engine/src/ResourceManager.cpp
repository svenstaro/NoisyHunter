#include "ResourceManager.hpp"

namespace Engine{

ResourceManager::ResourceManager() {}
/*ResourceManager::ResourceManager(Root* root) {
    mRoot = root;
}*/
ResourceManager::~ResourceManager() {}

bool ResourceManager::AddImage(const boost::filesystem::path& path, const std::string& imgname,
    const sf::Uint16 width, const sf::Uint16 height, const std::string& key) {

    // create Original File Path
    std::string originalFile = (path / imgname).string();


    // if the optional param key is not given, use the basename as key
    std::string image_key = "";
    if(key == "") {
        image_key = boost::filesystem::basename(originalFile);
    } else {
        image_key = key;
    }

    // Create Cache Paths
	boost::filesystem::path cacheDir = (path / "cached").string();
    std::string cacheFile = (cacheDir / image_key ).string()+".png";

    // if an image with that key already exists in the dictionary, return
    if(mImages.count(image_key) != 0) {
        return true;
    }

	// Log output
	std::cout << "Caching image " << originalFile << std::endl;

	// Create cache directory
	boost::filesystem::create_directory(cacheDir.string());

	// Load, convert and save image (originalFile > cacheFile)
	Magick::Image mimage;
	mimage.backgroundColor(Magick::Color(0,0,0,65535));
	mimage.read(originalFile);
	mimage.zoom(Magick::Geometry(width, height));
	mimage.depth(8);
	mimage.write(cacheFile);

	// Load cached File
	sf::Image sfimage;
	sfimage.LoadFromFile(cacheFile);
	sfimage.SetSmooth(false);

	// Save loaded Image in Dictionary
	// mImages.insert(new std::pair<std::string, sf::Image>(image_key, sfimage));
	mImages[image_key] = sfimage;

    return true;
}

const sf::Image& ResourceManager::GetImage(const std::string& img) {
    // TODO: if not in map argh!!!
	return mImages[img];
}


void ResourceManager::AddFont(sf::Font& font, std::string key) {
    mFonts[key] = font;
}
const sf::Font& ResourceManager::GetFont(const std::string& key) {
    return mFonts[key];
}


}
