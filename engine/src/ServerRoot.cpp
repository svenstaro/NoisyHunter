#include "ServerRoot.hpp"

namespace Engine{

void ServerRoot::StartMainLoop(){
    while (!mShutdownRequested){
        //mStateManager.Update();
    }
}


const NetworkManager* ServerRoot::GetNetworkManager() const{
    return &mNetworkServer;
}

}
