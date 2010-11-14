#include "ResourceManager.hpp"
#include "Root.hpp"

namespace Engine {

ResourceManager::ResourceManager() {
	mMaxImageQueueSize = 0;
}

ResourceManager::~ResourceManager() {}

void ResourceManager::AddImageToLoadingQueue(const boost::filesystem::path& path,
											 const std::string& imgname,
											 const float width,
											 const float height,
											 const std::string& key) {

	ImageProperties p(path, imgname, width, height, key);
	mImagesToLoad.push(p);

	if(mMaxImageQueueSize < mImagesToLoad.size())
		mMaxImageQueueSize = mImagesToLoad.size();
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
							   const float width,
							   const float height,
							   const std::string& key) {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

	if(!boost::filesystem::is_regular_file(path/imgname)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried loading image path'"+(path/imgname).string()+"' but this image path doesn't exist!");
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
	mimage.backgroundColor(Magick::Color(0, 0, 0, 65535));
	mimage.density(Magick::Geometry(144, 144));
	mimage.read(originalFile);
	// Conver floats to view pixels so that images will always be at the same scale
	const Vector2D vec(Coordinates::WorldFloatToWorldPixel(Vector2D(width, height)));
	mimage.zoom(Magick::Geometry(vec.x, vec.y));
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
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried getting image '"+img+"' but this image doesn't exist!");
		exit(1);
	}
}

bool ResourceManager::AddMusic(const boost::filesystem::path& path, const std::string& music_name, const std::string& key) {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

	if(!boost::filesystem::is_regular_file(path/music_name)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried loading music path'"+(path/music_name).string()+"' but this music path doesn't exist!");
		exit(1);
	}

    // create Original file path
    std::string originalFile = (path / music_name).string();


    // if the optional param key is not given, use the basename as key
    std::string music_key = "";
    if(key == "") {
        music_key = boost::filesystem::basename(originalFile);
    } else {
        music_key = key;
    }

    // if a music with that key already exists in the dictionary, return
    if(mMusic.count(music_key) != 0) {
        return true;
    }

	sf::Music* sfmusic = new sf::Music;
	if(!sfmusic->OpenFromFile(originalFile)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried loading music '"+(originalFile)+"' but it failed hard!");
		exit(1);
	}

	mMusic[music_key] = sfmusic;

    return true;
	
}

const sf::Music* ResourceManager::GetMusic(const std::string& music) {
	if(mMusic.count(music) >= 1) {
		return mMusic[music];
	} else {
		auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried getting music '"+(music)+"' but this music doesn't exist!");
		exit(1);
	}
}

bool ResourceManager::AddSoundBuffer(const boost::filesystem::path& path, const std::string& sound_name, const std::string& key) {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

	if(!boost::filesystem::is_regular_file(path/sound_name)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried loading sound path'"+(path/sound_name).string()+"' but this sound path doesn't exist!");
		exit(1);
	}

    // create Original file path
    std::string originalFile = (path / sound_name).string();


    // if the optional param key is not given, use the basename as key
    std::string sound_key = "";
    if(key == "") {
        sound_key = boost::filesystem::basename(originalFile);
    } else {
        sound_key = key;
    }

    // if a sound with that key already exists in the dictionary, return
    if(mSoundBuffers.count(sound_key) != 0) {
        return true;
    }

	sf::SoundBuffer sound_buffer;
	if(!sound_buffer.LoadFromFile(originalFile)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried loading sound '"+(originalFile)+"' but it failed hard!");
		exit(1);
	}


	mSoundBuffers[sound_key] = sound_buffer;

    return true;
	
}

const sf::SoundBuffer& ResourceManager::GetSoundBuffer(const std::string& sound) {
	if(mSoundBuffers.count(sound) >= 1) {
		return mSoundBuffers[sound];
	} else {
		auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_RESOURCEMANAGER, "Tried getting sound '"+(sound)+"' but this sound doesn't exist!");
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
