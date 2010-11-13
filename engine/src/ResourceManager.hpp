#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <iostream>
#include <queue>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ImageMagick/Magick++.h>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "AnimatedSprite.hpp"
#include "Coordinates.hpp"

namespace Engine {

enum MouseCursor {
	MOUSECURSOR_ARROW	= 10000,
	MOUSECURSOR_POINTER	= 10001,
	MOUSECURSOR_BUSY	= 10002,
	MOUSECURSOR_HELP	= 10003,
	MOUSECURSOR_MOVE	= 10004,
	MOUSECURSOR_NO		= 10005,
	MOUSECURSOR_SELECT	= 10006
};

struct LoadingStatus {
public:
	LoadingStatus() {}
	void SetTotalImages(const int total_images) {
		mTotalImages = total_images;
	}
	void SetImagesLoaded(const int images_loaded) {
		mImagesLoaded = images_loaded;
	}
	void IncreaseImagesLoaded() {
		mImagesLoaded++;
	}
	const int GetImagesLoaded() const {
		return mImagesLoaded;
	}
	const int GetTotalImages() const {
		return mTotalImages;
	}
	const float GetPercentage() const {
		if(mTotalImages == 0) return 1.f;
		return mImagesLoaded * 1.f / mTotalImages;
	}
	const bool IsFinished() const {
		return mImagesLoaded >= mTotalImages;
	}
private:
	int mImagesLoaded;
	int mTotalImages;
};

struct ImageProperties{
public:
	ImageProperties(const boost::filesystem::path& path,
					const std::string& imgname,
					const float width,
					const float height,
					const std::string& key="") {

		Path = path;
		Name = imgname;
		Width = width;
		Height = height;
		Key = key;
	}

	boost::filesystem::path Path;
	std::string Name;
	float Width;
	float Height;
	std::string Key;
};

class ResourceManager {
public:
    ResourceManager();

    ~ResourceManager();

	void AddImageToLoadingQueue(const boost::filesystem::path& path,
								const std::string& imgname,
								const float width,
								const float height,
								const std::string& key="");

	void LoadAllQueuedImagesInBackground();
	static void LoadAllQueuedImages(void* data);

	void LoadNextImage();
	const LoadingStatus GetLoadingStatus();

    bool AddImage(const boost::filesystem::path& path, const std::string& imgname,
        const float width, const float height, const std::string& key="");
    const sf::Image& GetImage(const std::string& img);

	bool AddMusic(const boost::filesystem::path& path, const std::string& music_name, const std::string& key="");
	const sf::Music* GetMusic(const std::string& music);

	bool AddSoundBuffer(const boost::filesystem::path& path, const std::string& sound, const std::string& key="");
	const sf::SoundBuffer& GetSoundBuffer(const std::string& sound);

    void AddFont(sf::Font& font, std::string key);
    const sf::Font& GetFont(const std::string& key);

	void SetCursorSprite(AnimatedSprite& sprite, const sf::Uint16 key);
	AnimatedSprite& GetCursorSprite();
	void SetCursor(const sf::Uint16 key);
	const sf::Uint16 GetCursor() const;
private:
	std::queue<ImageProperties> mImagesToLoad;
	std::queue<sf::Music> mMusicToLoad;

	boost::ptr_map<std::string, sf::Image> mImages;
	boost::ptr_map<std::string, sf::Font> mFonts;
	boost::ptr_map<sf::Uint16, AnimatedSprite> mCursors;
	sf::Uint16 mCurrentCursor;
	sf::Thread* mLoadingThread;

	boost::ptr_map<std::string, sf::Music*> mMusic;
	boost::ptr_map<std::string, sf::SoundBuffer> mSoundBuffers;
	LoadingStatus mLoadingStatus;
};

}

#endif
