#include "RootServer.hpp"

namespace Engine{

void RootServer::StartMainLoop(){
    while (!mShutdownRequested){
        //mStateManager.Update();
    }
}


const NetworkManager* ServerRoot::GetNetworkManager() const{
    return &mNetworkServer;
}

}
