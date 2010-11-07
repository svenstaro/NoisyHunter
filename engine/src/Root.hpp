#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <math.h>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/program_options.hpp>

#include "NetworkManager.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "LogManager.hpp"
#include "LogCommand.hpp"
#include "IdManager.hpp"
#include "AnimatedSprite.hpp"

namespace Engine {

enum RenderMode {
	RENDERMODE_WORLD,
	RENDERMODE_GUI
};

class Root : public boost::serialization::singleton<Root> {
public:
    Root();
    ~Root();

    void InitializeAsServer(const sf::Uint16 server_port,
							bool is_verbose);
    void InitializeAsClient(const sf::VideoMode& video_mode, 
							const std::string& window_title, 
							const bool is_fullscreen,
                            const sf::IpAddress& server_ip, 
							const sf::Uint16 server_port,
							const std::string name,
							bool is_verbose);

    //void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullsreen = false);
    void StartMainLoop();

    // Request a Shutdown. Engine will stop at the end of current loop iteration
    void RequestShutdown();

    // Manager Getter
    InputManager* GetInputManagerPtr();
    NetworkManager* GetNetworkManagerPtr();
    StateManager* GetStateManagerPtr();
    ResourceManager* GetResourceManagerPtr();
    LogManager* GetLogManagerPtr();
	IdManager* GetIdManagerPtr();

	void SetMouseHidden(const bool mouse_hidden);
    const Vector2D GetWindowSize() const;
	const sf::View& GetCurrentView() const;
	const sf::View& GetWorldView() const;

    Vector2D GetMousePosition() const;
	const sf::Input& GetInput() const;
    const std::string& GetClientName() const;
    sf::Uint16 GetClientId() const;
    void SetClientId(const sf::Uint16 client_id);

	void SetWorldPixelsPerFloat(const float ppf);
	const float GetWorldPixelsPerFloat() const;

	const float GetRunTime() const;

	float GetFps() const;
	float GetAverageFps() const;
	const bool IsServer() const;

	void SetRenderMode(const RenderMode mode);
	void SetTakeScreenshot(const bool take_screenshot);
	void CenterViewAt(const Vector2D center);

private:
    bool mIsServer;
    bool mShutdownRequested;

    // these members are for use in client mode only !
	sf::RenderWindow mRenderWindow;	// create Render Window first as Input Manager needs it in constructor
	sf::View mWorldView;			// switch to this view for world rendering, switch back for GUI rendering
    InputManager mInputManager;
    ResourceManager mResourceManager;
    std::string mClientName;
	sf::Int16 mClientId;
	float mWorldPixelsPerFloat;		// Float coordinates are multiplied by this>.
	bool mTakeScreenshot;
	// For average FPS calculation
	sf::Uint32 mTotalNumFrames;
    
	sf::Clock mFrameTimeClock;
    sf::Clock mRunTimeClock;
    StateManager mStateManager;
    NetworkManager mNetworkManager;
	LogManager mLogManager;
	IdManager mIdManager;
};

}

#endif
