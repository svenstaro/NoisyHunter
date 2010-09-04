#ifndef ROOT_HPP
#define ROOT_HPP

namespace Engine{

class Root {
public:
    //void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullsreen = false);
    virtual void StartMainLoop() = 0;

    // Request a Shutdown. Engine will stop at the end of current loop iteration
    void RequestShutdown();

    NetworkManager& GetNetworkManager() const;
    StateManager& GetStateManger() const;

protected:
    bool mShutdownRequested;

private:
    NetworkManager mNetworkManager;
    StateManager mStateManager;
};

}

#endif
