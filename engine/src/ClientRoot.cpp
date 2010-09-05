#include "ClientRoot.hpp"

namespace Engine {

void ClientRoot::Initialize(sf::VideoMode video_mode, std::string window_title, bool fullscreen){
    mShutdownRequested = false;

    if (fullscreen){
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen);
    } else {
        mRenderWindow.Create(video_mode, window_title);
    }
}


void ClientRoot::StartMainLoop(){
    while (mRenderWindow.IsOpened()){

        sf::Event e;
        while (mRenderWindow.GetEvent(e)){
            mInputManager.HandleEvent(e);
        }

        //mStateManager.Update();

        // Clear screen
        mRenderWindow.Clear();
        //mStateManager.Draw();
        // Update the window
        mRenderWindow.Display();

        // check if a shutdown has been requested
        if (mShutdownRequested)
            mRenderWindow.Close();

    }


}



const NetworkManager* ClientRoot::GetNetworkManager() const{
    return &mNetworkClient;
}

}
