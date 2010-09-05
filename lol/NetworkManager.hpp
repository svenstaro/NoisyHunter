#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>

//#include "Root.hpp"
#include "Entity.hpp"


namespace Engine {

class NetworkManager {
public:
    NetworkManager();
	//NetworkManager(Root* root);
	~NetworkManager();

    // method used when in server mode
    void HandleClients();

    void PreparePacket();
    void AddEntity(Entity& entity);
    void SendPacket();

private:
    // general members
    bool mIsServer;

};

}

#endif
