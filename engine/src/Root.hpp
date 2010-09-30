#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/program_options.hpp>

#include "NetworkManager.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"

namespace Engine {

class Root : public boost::serialization::singleton<Root> {
public:
    Root();
    ~Root();

    void InitializeAsServer(const sf::Uint16 server_port);
    void InitializeAsClient(const sf::VideoMode& video_mode, 
							const std::string& window_title, 
							const bool is_fullscreen,
                            const sf::IPAddress& server_ip, 
							const sf::Uint16 server_port,
							const std::string name);

    //void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullsreen = false);
    void StartMainLoop();

    // Request a Shutdown. Engine will stop at the end of current loop iteration
    void RequestShutdown();

    // Manager Getter
    InputManager* GetInputManagerPtr();
    NetworkManager* GetNetworkManagerPtr();
    StateManager* GetStateManagerPtr();
    ResourceManager* GetResourceManagerPtr();

	void SetMouseHidden(const bool mouse_hidden);
    const Vector2D GetWindowSize() const;

    Vector2D GetMousePosition() const;
    const std::string& GetClientName() const;

	// LOGGING
	static void Log(LogLevel level, LogOrigin origin, std::string message);

private:
    bool mIsServer;
    bool mShutdownRequested;

    // these members are for use in client mode only !
    sf::RenderWindow mRenderWindow; // create Render Window first as Input Manager needs it in constructor
    InputManager mInputManager;
    ResourceManager mResourceManager;
    std::string mClientName;
    
    sf::Clock mClock;
    StateManager mStateManager;
    NetworkManager mNetworkManager;
	LogManager mLogManager;
};

}

#endif
