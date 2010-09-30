#include "Root.hpp"

namespace Engine {

Root::Root() {
    mShutdownRequested = false;
}
Root::~Root() {}

Vector2D Root::GetMousePosition() const {
    return Vector2D(mRenderWindow.GetInput().GetMouseX(),
                    mRenderWindow.GetInput().GetMouseY());
}

void Root::InitializeAsServer(const sf::Uint16 server_port,
							  bool verbose) {
    mIsServer = true;
	mVerbose = verbose;
    //mStateManager = StateManager();
    // mNetworkManager = NetworkManager();
	mNetworkManager.InitializeAsServer(server_port);
}

void Root::InitializeAsClient(const sf::VideoMode& video_mode, 
							  const std::string& window_title, 
							  const bool is_fullscreen,
							  const sf::IPAddress& server_ip, 
							  const sf::Uint16 server_port,
							  const std::string name,
							  bool verbose) {

    mIsServer = false;

    sf::WindowSettings Settings;
    Settings.DepthBits         = 24; // Request a 24 bits depth buffer
    Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
    Settings.AntialiasingLevel = 8;  // Request 2 levels of antialiasing

    // Create Render Window
    if(is_fullscreen)
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen, Settings);
    else
        mRenderWindow.Create(video_mode, window_title, sf::Style::Close, Settings);

    //mInputManager = InputManager();
    //mStateManager = StateManager();
    //mResourceManager = ResourceManager();

    // Create and Initialize Network Manager
    // mNetworkManager = NetworkManager();
    mClientName = name;
	mVerbose = verbose;
    mNetworkManager.InitializeAsClient(server_ip, server_port, name);
}

void Root::StartMainLoop() {
    if(mIsServer) {
        // SERVER MAIN LOOP
		sf::Clock Clock;
        
		const float fps = 60.f;
		const float dt = 1/fps;
        float timebudget = 0.f;
        
        while(!mShutdownRequested) {
            float time_delta = Clock.GetElapsedTime();
            Clock.Reset();
            timebudget += time_delta;
                       
            // update simulation
			while(time_delta < timebudget) {
                mStateManager.Update(dt);
                timebudget -= dt;
			}
            // do networking stuff
            mNetworkManager.Receive();
            
            mNetworkManager.PreparePacket();
            mStateManager.AppendAllEntitiesToPacket();
			mNetworkManager.SendPacket();
        }
    } else {
        // CLIENT MAIN LOOP
		sf::Clock Clock;
		const float fps = 60.f;
		const float dt = 1/fps;
        float timebudget = 0.f;
        
        while(mRenderWindow.IsOpened()) {
            float time_delta = mClock.GetElapsedTime();
            mClock.Reset();
            
            // Always prepare packet before handling events, as there 
            // might be actions to be inserted into packet.
            mNetworkManager.PreparePacket();
            
            // Handle events.
            sf::Event e;
            while(mRenderWindow.GetEvent(e)) {
                mInputManager.HandleEvent(e);
                mStateManager.HandleEvent(e);
            }
            
            // Network receiving.
            mNetworkManager.Receive();
            
            // There will be a snapshot to be processed from time to time,
            // but this still has to be updated to current time.
                        
			// Send the prepared packet.
			mNetworkManager.SendPacket();
            
            timebudget += time_delta;
            // Update simulation with fixed timestep.
			while(time_delta < timebudget) {
                mStateManager.Update(dt);
                timebudget -= dt;
			}          
            
            // Render the image.
            mRenderWindow.Clear(sf::Color(0,0,0));
            mStateManager.Draw(&mRenderWindow);
            mRenderWindow.Display();

            // Check whether a shutdown has been requested.
            if(mShutdownRequested)
                mRenderWindow.Close();
        }
    }
}

void Root::RequestShutdown() {
    mShutdownRequested = true;
}

// MANAGER GETTER
ResourceManager* Root::GetResourceManagerPtr() {
    return &mResourceManager;
}

InputManager* Root::GetInputManagerPtr() {
    return &mInputManager;
}

StateManager* Root::GetStateManagerPtr(){
    return &mStateManager;
}

NetworkManager* Root::GetNetworkManagerPtr() {
    return &mNetworkManager;
}

const Vector2D Root::GetWindowSize() const {
    return Vector2D(mRenderWindow.GetWidth(), mRenderWindow.GetHeight());
}

void Root::SetMouseHidden(const bool mouse_hidden) {
	mRenderWindow.ShowMouseCursor(!mouse_hidden);
}

const std::string& Root::GetClientName() const {
    return mClientName;
}

void Root::Log(LogLevel level, LogOrigin origin, const std::string& message) {
	mLogManager.Log(LogLevel level, LogOrigin origin, const std::string& message);
}

}
