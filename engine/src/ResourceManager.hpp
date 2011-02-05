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
#include "GuiTexture.hpp"

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

struct ImageProperties {
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

	sf::Uint16 LoadNextImage();
	sf::Uint16 GetImagesToLoadLeft() const;
	sf::Uint16 GetMaxImageQueueSize() const;
	float GetPercentageLoadingDone() const;

    bool AddImage(const boost::filesystem::path& path, const std::string& imgname,
        const float width, const float height, const std::string& key="");
    const sf::Image& GetImage(const std::string& img);

	bool AddSoundBuffer(const boost::filesystem::path& path, const std::string& sound, const std::string& key="");
	const sf::SoundBuffer& GetSoundBuffer(const std::string& sound);

    void AddFont(sf::Font& font, std::string key);
    const sf::Font& GetFont(const std::string& key);

	void AddGuiTexture(GuiTexture gui_texture);
	const GuiTexture& GetGuiTexture(const std::string& name);

	void SetCursorSprite(AnimatedSprite& sprite, const sf::Uint16 key);
	AnimatedSprite& GetCursorSprite();
	void SetCursor(const sf::Uint16 key);
	sf::Uint16 GetCursor() const;
private:
	std::queue<ImageProperties> mImagesToLoad;
	std::queue<sf::Music> mMusicToLoad;

	boost::ptr_map<std::string, sf::Image> mImages;
	boost::ptr_map<std::string, sf::Font> mFonts;
	boost::ptr_map<sf::Uint16, AnimatedSprite> mCursors;
	sf::Uint16 mCurrentCursor;

	boost::ptr_map<std::string, sf::Music> mMusic;
	boost::ptr_map<std::string, sf::SoundBuffer> mSoundBuffers;

	boost::ptr_map<std::string, GuiTexture> mGuiTextures;

	sf::Uint16 mMaxImageQueueSize;
};

}

#endif
