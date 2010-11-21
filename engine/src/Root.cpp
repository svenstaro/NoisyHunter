#include "Root.hpp"

namespace Engine {

Root::Root() {
    mShutdownRequested = false;
    mClientId = -1;
	mTotalNumFrames = 0;
}
Root::~Root() {}

Vector2D Root::GetMousePosition() const {
	return Vector2D(GetInput().GetMouseX(),
					GetInput().GetMouseY());
}

const sf::Input& Root::GetInput() const{
	return mRenderWindow.GetInput();
}

void Root::InitializeAsServer(const sf::Uint16 server_port,
							  bool is_verbose) {
    mIsServer = true;

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->SetVerbose(is_verbose);
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_STATE, "Initializing Root as server.");

    //mStateManager = StateManager();
    // mNetworkManager = NetworkManager();
	mNetworkManager.InitializeAsServer(server_port);

	mTakeScreenshot = false;
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
	logmgr->SetVerbose(is_verbose);
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_STATE, "Initializing Root as client.");

    sf::ContextSettings Settings;
    Settings.DepthBits         = 24; // Request a 24 bits depth buffer
    Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 8;  // Request 8 levels of antialiasing

    // Create Render Window
    if(is_fullscreen)
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen, Settings);
    else
        mRenderWindow.Create(video_mode, window_title, sf::Style::Close, Settings);

	// Create & initialize world view
	mWorldView.Reset(sf::FloatRect(0,0,800,600));
	mWorldView.SetViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	// Load Engine Resources (Default GUI etc.)
	int cursor_size = 24;
	mResourceManager.AddImage(boost::filesystem::path("../engine/gui"),"cursors.svg", cursor_size*16.f/mWorldPixelsPerFloat, cursor_size*16.f/mWorldPixelsPerFloat, "gui.default.cursors");
	AnimatedSprite arrow;
	arrow.SetImage(mResourceManager.GetImage("gui.default.cursors"));
	arrow.SetSubRectSize(sf::Vector2f(cursor_size,cursor_size));
	arrow.SetSubRectOffset(sf::Vector2f(0,0));
	arrow.SetFPS(0);
	arrow.SetNumFrames(1);
	mResourceManager.SetCursorSprite(arrow, MOUSECURSOR_ARROW);

	AnimatedSprite busy;
	busy.SetImage(mResourceManager.GetImage("gui.default.cursors"));
	busy.SetSubRectSize(sf::Vector2f(cursor_size,cursor_size));
	busy.SetSubRectOffset(sf::Vector2f(0,cursor_size));
	busy.SetFPS(8);
	busy.SetNumFrames(8);
	mResourceManager.SetCursorSprite(busy, MOUSECURSOR_BUSY);

	mResourceManager.SetCursor(MOUSECURSOR_ARROW);


    //mInputManager = InputManager();
    //mStateManager = StateManager();
    //mResourceManager = ResourceManager();

    // Create and Initialize Network Manager
    // mNetworkManager = NetworkManager();
    mClientName = name;
    mNetworkManager.InitializeAsClient(server_ip, server_port, name);

	mTakeScreenshot = false;
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
			mTotalNumFrames++;
			sf::Sleep(0.001f);
			mStateManager.BeginFrame();
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
		sf::Clock PingClock;
        
        while(mRenderWindow.IsOpened()) {
			mTotalNumFrames++;
			mStateManager.BeginFrame();
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
			// Update mouse cursor
			AnimatedSprite& cursor = mResourceManager.GetCursorSprite();
			cursor.Update(time_delta);

            
			if(PingClock.GetElapsedTime() >= 1.0f) {
				PingClock.Reset();
				GetNetworkManagerPtr()->SendPing();
			}
            // Render the image.
			mRenderWindow.Clear(sf::Color(0,0,0));
            mStateManager.Draw(&mRenderWindow);
			// Render mouse cursor
			cursor.SetPosition(GetMousePosition().x, GetMousePosition().y);
			mRenderWindow.Draw(cursor);
			if(mTakeScreenshot) {
				sf::Image shot;
				shot.CopyScreen(mRenderWindow);
				// TODO: Change this to png when it works.
				shot.SaveToFile("screen.jpg");
				mTakeScreenshot = false;
			}
            mRenderWindow.Display();

            // Check whether a shutdown has been requested.
            if(mShutdownRequested)
                mRenderWindow.Close();
        }
		// End all states
		mStateManager.Shutdown();
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

const sf::View& Root::GetCurrentView() const {
	return mRenderWindow.GetView();
}

const sf::View& Root::GetWorldView() const {
	return mWorldView;
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

void Root::SetWorldPixelsPerFloat(const float ppf) {
	mWorldPixelsPerFloat = ppf;
}

float Root::GetWorldPixelsPerFloat() const {
	return mWorldPixelsPerFloat;
}

float Root::GetRunTime() const {
	return mRunTimeClock.GetElapsedTime();
}

float Root::GetFps() const {
	return floor(1 / mRenderWindow.GetFrameTime());
}

float Root::GetAverageFps() const {
	return floor(mTotalNumFrames / GetRunTime());
}

bool Root::IsServer() const {
	return mIsServer;
}

void Root::SetRenderMode(const RenderMode mode) {
	if (mIsServer)
		mLogManager.Log(LOGLEVEL_ERROR, LOGORIGIN_ROOT, "Tried to switch render mode in server.");
	else if (mode == RENDERMODE_WORLD)
		mRenderWindow.SetView(mWorldView);
	else if (mode == RENDERMODE_GUI)
		mRenderWindow.SetView(mRenderWindow.GetDefaultView());
}

void Root::SetTakeScreenshot(const bool take_screenshot) {
	mTakeScreenshot = take_screenshot;
}

void Root::CenterViewAt(const Vector2D center) {
	mWorldView.SetCenter(center.x, center.y);
}

}
