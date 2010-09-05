#include "RootServer.hpp"

namespace Engine{

void RootServer::StartMainLoop(){
    while (!mShutdownRequested){
        //mStateManager.Update();
    }
}


NetworkManager* RootServer::GetNetworkManager(){
    return &mNetworkServer;
}

}
