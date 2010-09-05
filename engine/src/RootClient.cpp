#include "RootClient.hpp"

namespace Engine {

void RootClient::Initialize(sf::VideoMode video_mode, std::string window_title, bool fullscreen){
    mShutdownRequested = false;

    if (fullscreen){
        mRenderWindow.Create(video_mode, window_title, sf::Style::Fullscreen);
    } else {
        mRenderWindow.Create(video_mode, window_title);
    }
}


void RootClient::StartMainLoop(){
    while (mRenderWindow.IsOpened()){
        //mInputManager.HandleEvents();

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




/*ResourceManager& RootClient::GetResourceManager() const {
    return mResourceManager;
}

InputManager& RootClient::GetInputManger() const {
    return mInputManager;
}*/


}
