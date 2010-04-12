#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <SFML/System.hpp>

#include <string>

#include "network.hpp"

// ServerApp is the manager class for the server
class ServerApp {
public:
    // constructor only sets values, no work is done in the constructor!
    ServerApp(sf::Uint16 port);

    // default destructor, no work takes place here
    ~ServerApp();

    // do init stuff and return success status
    bool Init();

    // main loop
    void Run();

    // safely shutdown network
    void Cleanup();

private:
    sf::Uint16 mPort;
};

#endif
