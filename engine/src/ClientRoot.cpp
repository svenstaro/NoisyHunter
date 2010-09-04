#include "ClientRoot.hpp"

namespace Engine {

void ClientRoot::Initialize(sf::VideoMode video_mode, std::string window_title, bool fullsreen){
    mShutdownRequested = false;

    if (fullscreen){
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen);
    } else {
        mRenderWindow.Create(video_mode, window_title);
    }
}


void ClientRoot::StartMainLoop(){
    while (mRenderWindow.IsOpened()){
        mInputManager.HandleEvents();

        mStateManager.Update();

        // Clear screen
        mRenderWindow.Clear();
        mStateManager.Draw();
        // Update the window
        mRenderWindow.Display();

        // check if a shutdown has been requested
        if (mShutdownRequested)
            mRenderWindow->Close();

    }


}




ResourceManager& ClientRoot::GetResourceManager() const {
    return mResourceManager;
}

InputManager& ClientRoot::GetInputManger() const {
    return mInputManager;
}


}
