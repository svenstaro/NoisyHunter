#ifndef ROOT_HPP
#define ROOT_HPP

#include "NetworkManager.hpp"
//#include "StateManager.hpp"
#include "InputManager.hpp"

namespace Engine{

class Root {
public:
    //void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullsreen = false);
    virtual void StartMainLoop() = 0;

    // Request a Shutdown. Engine will stop at the end of current loop iteration
    void RequestShutdown();

  /*
    StateManager& GetStateManger() const;
    ResourceManager& GetResourceManager() const;*/
    virtual const InputManager* GetInputMangerPtr() const;
    virtual const NetworkManager* GetNetworkManager() const = 0;

protected:
    bool mShutdownRequested;

    /*
    StateManager mStateManager;
    ResourceManager mResourceManager; */
    InputManager mInputManager;
};

}

#endif
