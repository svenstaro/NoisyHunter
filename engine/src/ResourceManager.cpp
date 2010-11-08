#include "ResourceManager.hpp"
#include "Root.hpp"

namespace Engine {

ResourceManager::ResourceManager() {
	mMaxImageQueueSize = 0;
}

ResourceManager::~ResourceManager() {}

void ResourceManager::AddImageToLoadingQueue(const boost::filesystem::path& path,
											 const std::string& imgname,
											 const sf::Uint16 width,
											 const sf::Uint16 height,
											 const std::string& key) {

	ImageProperties p(path, imgname, width, height, key);
	mImagesToLoad.push(p);

	if(mMaxImageQueueSize < mImagesToLoad.size())
		mMaxImageQueueSize = mImagesToLoad.size();
}

void ResourceManager::LoadAllQueuedImages(void* data) {
	sf::Context context;
	auto resmgr = Root::get_mutable_instance().GetResourceManagerPtr();
	while(resmgr->GetPercentageLoadingDone() < 1) {
		resmgr->LoadNextImage();
	}
}

void ResourceManager::StartLoadingAllQueuedImagesInBackground() {
	sf::Thread thread(&ResourceManager::LoadAllQueuedImages);
	thread.Launch();
}

const sf::Uint16 ResourceManager::LoadNextImage() {

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

	if(mImagesToLoad.size() <= 0)
		return mMaxImageQueueSize;

	ImageProperties p = mImagesToLoad.front();
	mImagesToLoad.pop();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_RESOURCEMANAGER, "Loading image " + p.Key + " from queue.");
	if(!AddImage(p.Path, p.Name, p.Width, p.Height, p.Key))
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Could not load image " + p.Key);

	return int(mImagesToLoad.size());
}

const sf::Uint16 ResourceManager::GetImagesToLoadLeft() const {
	return int(mImagesToLoad.size());
}

const sf::Uint16 ResourceManager::GetMaxImageQueueSize() const {
	return mMaxImageQueueSize;
}

const float ResourceManager::GetPercentageLoadingDone() const {
	if(mMaxImageQueueSize == 0)
		return 1.f;
	else
		return 1.f - int(mImagesToLoad.size()) * 1.f / mMaxImageQueueSize;
}

bool ResourceManager::AddImage(const boost::filesystem::path& path,
							   const std::string& imgname,
							   const sf::Uint16 width,
							   const sf::Uint16 height,
							   const std::string& key) {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

	if(!boost::filesystem::is_regular_file(path/imgname)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_CLIENTMANAGER, "Tried loading image path'"+(path/imgname).string()+"' but this image path doesn't exist!");
		exit(1);
	}

    // create Original file path
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
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_RESOURCEMANAGER, "Caching image " + originalFile);

	// Create cache directory
	boost::filesystem::create_directory(cacheDir.string());

	// Load, convert and save image (originalFile > cacheFile)
	Magick::Image mimage;
	mimage.backgroundColor(Magick::Color(0,0,0,65535));
	mimage.density(Magick::Geometry(144,144));
	mimage.read(originalFile);
	mimage.zoom(Magick::Geometry(width, height));
	mimage.depth(8);
	mimage.write(cacheFile);

	// Load cached file
	sf::Image sfimage;
	sfimage.LoadFromFile(cacheFile);
	sfimage.SetSmooth(true);

	// Save loaded Image in Dictionary
	// mImages.insert(new std::pair<std::string, sf::Image>(image_key, sfimage));
	mImages[image_key] = sfimage;

    return true;
}

const sf::Image& ResourceManager::GetImage(const std::string& img) {
	if(mImages.count(img) >= 1) {
		return mImages[img];
	} else {
		auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_CLIENTMANAGER, "Tried getting image '"+img+"' but this image doesn't exist!");
		exit(1);
	}
}

void ResourceManager::AddFont(sf::Font& font, std::string key) {
    mFonts[key] = font;
}
const sf::Font& ResourceManager::GetFont(const std::string& key) {
    return mFonts[key];
}

void ResourceManager::SetCursorSprite(AnimatedSprite& sprite, const sf::Uint16 key) {
	mCursors[key] = sprite;
}

void ResourceManager::SetCursor(const sf::Uint16 key) {
	mCurrentCursor = key;
}

const sf::Uint16 ResourceManager::GetCursor() const {
	return mCurrentCursor;
}

AnimatedSprite& ResourceManager::GetCursorSprite() {
	return mCursors[mCurrentCursor];
}

}
