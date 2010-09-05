#include "Root.hpp"

namespace Engine{

Root::Root() {}
Root::~Root() {}


void Root::RequestShutdown(){
    mShutdownRequested = true;
}

/*NetworkManager& Root::GetNetworkManager() const {
    return mNetworkManager;
}

StateManager& Root::GetStateManger() const {
    return mStateManager;
}*/



/*ResourceManager& ClientRoot::GetResourceManager() const {
    return mResourceManager;
}*/


InputManager* Root::GetInputMangerPtr() {
    return &mInputManager;
}


}
