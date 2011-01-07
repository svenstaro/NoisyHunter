#include "Root.hpp"

#include "MusicManager.hpp"

namespace Engine {

MusicManager::MusicManager() {}

MusicManager::~MusicManager() {}

void MusicManager::Play(const std::string& trackname) {
	// Only attempt to do something if the trackname can be found in the map,
	// i.e. if it has been already been registered.
	if(mMusicTracks.count(trackname)) {

		// Only attempt to do something if we are not trying to play the
		// current track again.
		if(mCurrentMusic != trackname) {

			// Do not stop music if there is no current music, i.e., if this 
			// is the first track to play since starting the game.
			if(!mCurrentMusic.empty()) {
				Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_MUSICMANAGER, "Stopping music "+mCurrentMusic);
				mMusicTracks[mCurrentMusic]->Stop();
			}

			mCurrentMusic = trackname;
			Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_MUSICMANAGER, "Playing music "+trackname);
			mMusicTracks[mCurrentMusic]->Play();
		}
	} else {
		Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_ERROR, LOGORIGIN_MUSICMANAGER, "Tried playing unregistered music track.");
		exit(1);
	}
}

void MusicManager::Pause() {
	mMusicTracks[mCurrentMusic]->Pause();
}

void MusicManager::Stop() {
	mMusicTracks[mCurrentMusic]->Stop();
}

bool MusicManager::Register(const boost::filesystem::path& path,
							const std::string& trackname,
							const float volume,
							const float pitch) {
	if(!boost::filesystem::is_regular_file(path/trackname)) {
		Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_ERROR, LOGORIGIN_MUSICMANAGER, "Tried registering music path '"+(path/trackname).string()+"' but this music path doesn't exist!");
		exit(1);
	}

    // if music already is registered, return
    if(mMusicTracks.count((path/trackname).string()) != 0) {
        return true;
    }

	// log output
	Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_VERBOSE, LOGORIGIN_MUSICMANAGER, "Registering music track '"+(path/trackname).string()+"'");

	boost::shared_ptr<sf::Music> music(new sf::Music());
	mMusicTracks[trackname] = music;
	mMusicTracks[trackname]->OpenFromFile((path/trackname).string());
	mMusicTracks[trackname]->SetPitch(pitch);
	mMusicTracks[trackname]->SetVolume(volume);
	mMusicTracks[trackname]->SetLoop(true);
	return true;
}

}
