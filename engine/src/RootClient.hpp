#ifndef ROOTCLIENT_HPP
#define ROOTCLIENT_HPP

#include <SFML/Graphics.hpp>
#include "Root.hpp"
#include "InputManager.hpp"

namespace Engine{

class RootClient : public Root {
public:
    void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullscreen = false);
    void StartMainLoop();

    const NetworkManager* GetNetworkManager() const:
}

private:
    sf::RenderWindow mRenderWindow;
    NetworkClient mNetworkClient;
};

}

#endif
