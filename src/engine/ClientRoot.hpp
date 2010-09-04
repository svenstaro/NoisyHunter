#ifndef CLIENTROOT_HPP
#define CLIENTROOT_HPP

#include <SFML/Graphics.hpp>
#include "Root.hpp"

namespace Engine{

class ClientRoot : public Root {
public:
    void Initialize(sf::VideoMode video_mode, std::string window_title, bool fullscreen = false);
    void StartMainLoop();

    /*ResourceManager& GetResourceManager() const;
    InputManager& GetInputManger() const;*/
private:
    sf::RenderWindow mRenderWindow;
/*
    ResourceManager mResourceManager;
    InputManager mInputManager;*/
};

}

#endif
