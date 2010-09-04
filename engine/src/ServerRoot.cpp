#include "ServerRoot.hpp"

void ServerRoot::StartMainLoop(){
    while (!mShutdownRequested){
        mStateManager.Update();
    }
}
