#include "Root.hpp"


namespace Engine{

Root::Root() {
    mShutdownRequested = false;
}
Root::~Root() {}

void Root::InitializeAsServer(const sf::Uint16 server_port){
    mIsServer = true;
    //mStateManager = StateManager();
    //mNetworkManager = NetworkManager();
    mNetworkManager.InitializeAsServer(server_port);
}

void Root::InitializeAsClient(const sf::VideoMode& video_mode, const std::string& window_title, const bool is_fullscreen,
                        const sf::IPAddress& server_ip, const sf::Uint16 server_port){

    mIsServer = false;

    // Create Render Window
    if (is_fullscreen){
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen);
    }
    else {
        mRenderWindow.Create(video_mode, window_title);
    }

    //mInputManager = InputManager();
    //mStateManager = StateManager();
    //mResourceManager = ResourceManager();

    // Create and Initialize Network Manager
    //mNetworkManager = NetworkManager();
    mNetworkManager.InitializeAsClient(server_ip, server_port);
}




void Root::StartMainLoop(){

    if (mIsServer) {

        // SERVER MAIN LOOP

        while (!mShutdownRequested){
            //mStateManager.Update();
        }


    }
    else {

        // CLIENT MAIN LOOP

        while (mRenderWindow.IsOpened()){
            float time_delta = 0.2;

            sf::Event e;
            while (mRenderWindow.GetEvent(e)){
                mInputManager.HandleEvent(e);
            }
            mStateManager.Update(time_delta);

            // Render the image
            mRenderWindow.Clear();
            // mStateManager.Draw();
            mRenderWindow.Display();

            // Check if a shutdown has been requested...
            if (mShutdownRequested)
                mRenderWindow.Close();

        }
    }

}


void Root::RequestShutdown(){
    mShutdownRequested = true;
}




// MANAGER GETTER

ResourceManager* Root::GetResourceManagerPtr() {
    return &mResourceManager;
}
InputManager* Root::GetInputMangerPtr() {
    return &mInputManager;
}
StateManager* Root::GetStateManagerPtr(){
    return &mStateManager;
}
NetworkManager* Root::GetNetworkManagerPtr() {
    return &mNetworkManager;
}


}
