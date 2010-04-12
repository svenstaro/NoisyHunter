#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_container.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>

#include "entity.hpp"
#include "network.hpp"

// ClientApp is the manager class for the client
class ClientApp {
public:
    // constructor only sets values, no work is done in the constructor!
    ClientApp(sf::Uint16 width, sf::Uint16 height, sf::Uint16 port);
    
    // default destructor, no work takes place here
    ~ClientApp();

    // do init stuff and return success status
    bool Init(); 

    // main loop
    void Run();

    // safely shutdown input, graphics and network
    void Cleanup();

private:
    sf::Uint16 mWidth;
    sf::Uint16 mHeight;
    sf::Uint16 mPort;
    sf::RenderWindow mRenderWin;
    sf::SocketUDP mSocket;

    boost::ptr_vector<IEntity> mEntityList;
};

#endif
