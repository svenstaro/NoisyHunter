#ifndef ROOTCLIENT_HPP
#define ROOTCLIENT_HPP

#include <SFML/Graphics.hpp>
#include "Root.hpp"
#include "InputManager.hpp"
#include "NetworkClient.hpp"

namespace Engine{

class RootClient : public Root {
public:
    void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullscreen = false);
    void StartMainLoop();

    NetworkManager* GetNetworkManager();

private:
    sf::RenderWindow mRenderWindow;
    NetworkClient mNetworkClient;
};

}

#endif
