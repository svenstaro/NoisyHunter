#include "Root.hpp"

namespace Engine{

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
}
*/

const InputManager* Root::GetInputMangerPtr() const {
    return &mInputManager;
}


}
