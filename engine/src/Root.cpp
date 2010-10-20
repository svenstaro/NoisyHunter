#include "Root.hpp"

namespace Engine {

Root::Root() {
    mShutdownRequested = false;
    mClientId = -1;
}
Root::~Root() {}

Vector2D Root::GetMousePosition() const {
    return Vector2D(mRenderWindow.GetInput().GetMouseX(),
                    mRenderWindow.GetInput().GetMouseY());
}

void Root::InitializeAsServer(const sf::Uint16 server_port,
							  bool is_verbose) {
    mIsServer = true;
	mIsVerbose = is_verbose;

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_STATE, "Initializing Root as server.");

    //mStateManager = StateManager();
    // mNetworkManager = NetworkManager();
	mNetworkManager.InitializeAsServer(server_port);
}

void Root::InitializeAsClient(const sf::VideoMode& video_mode, 
							  const std::string& window_title, 
							  const bool is_fullscreen,
							  const sf::IpAddress& server_ip, 
							  const sf::Uint16 server_port,
							  const std::string name,
							  bool is_verbose) {

    mIsServer = false;

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_STATE, "Initializing Root as client.");

    sf::ContextSettings Settings;
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
	mIsVerbose = is_verbose;
    mNetworkManager.InitializeAsClient(server_ip, server_port, name);
}

void Root::StartMainLoop() {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

    if(mIsServer) {
        // SERVER MAIN LOOP
        
		const float fps = 100.0f;
		const float dt = 1/fps;
		const float net_tick_rate = 10.f;
        float time_budget = 0.f;

		sf::Clock SnapClock;
        
        while(!mShutdownRequested) {
			sf::Sleep(0.001f);
            float frame_time = mFrameTimeClock.GetElapsedTime();
            mFrameTimeClock.Reset();
            time_budget += frame_time;
                       
            // update simulation
			while(time_budget >= dt) {
                mStateManager.Update(dt);
                time_budget -= dt;
			}

            // Receive packets from clients.
            mNetworkManager.Receive();
            
			// Only send if there are clients to send packets to.
			if(SnapClock.GetElapsedTime() >= 1.0f/net_tick_rate) {
				SnapClock.Reset();
				if(mNetworkManager.GetClientManagerPtr()->GetActiveClients() > 0) {
					mNetworkManager.PreparePacket();
					mStateManager.AppendAllEntitiesToPacket();
					logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Sending snapshot.");
					mNetworkManager.SendPacket();
				}
			}
        }
    } else {
        // CLIENT MAIN LOOP
		const float fps = 60.f;
		const float dt = 1/fps;
        float time_budget = 0.f;
        
        while(mRenderWindow.IsOpened()) {
            float time_delta = mFrameTimeClock.GetElapsedTime();
            mFrameTimeClock.Reset();
            
            // Always prepare packet before handling events, as there 
            // might be actions to be inserted into packet.
            //mNetworkManager.PreparePacket();
            
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
			//mNetworkManager.SendPacket();
            
            time_budget += time_delta;
            // Update simulation with fixed timestep.
			while(time_budget >= dt) {
                mStateManager.Update(dt);
                time_budget -= dt;
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

LogManager* Root::GetLogManagerPtr() {
	return &mLogManager;
}

IdManager* Root::GetIdManagerPtr() {
	return &mIdManager;
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
sf::Uint16 Root::GetClientId() const {
    return mClientId;
}
void Root::SetClientId(const sf::Uint16 client_id) {
    mClientId = client_id;
}

const float Root::GetRunTime() const {
	return mRunTimeClock.GetElapsedTime();
}

}
