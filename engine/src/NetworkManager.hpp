#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>

#include <boost/foreach.hpp>

#include <SFML/Network.hpp>

//#include "Root.hpp"
#include "Entity.hpp"
#include "ClientManager.hpp"
#include "NetworkCommands.hpp"

namespace Engine {

class NetworkManager {
public:
    NetworkManager();
	//NetworkManager(Root* root);
	~NetworkManager();

	void InitializeAsServer(const sf::Uint16 server_port);
	void InitializeAsClient(const sf::IPAddress server_ip, 
							const sf::Uint16 server_port);

    // method used when in server mode
    void HandleClients();
	void HandlePacket(sf::Packet packet, sf::IPAddress address, sf::Uint16 port);

    void PreparePacket();
    void AddEntity(Entity& entity);
    void SendPacket();

private:
    // general members
    bool mIsServer;
    //Root* mRoot;
	sf::SocketUDP mListener;
	sf::Packet mPacket;

    // members used when in server mode
	sf::SelectorUDP mServer_Selector;

    // members used when in client mode
    sf::IPAddress mClient_ServerIp;
    sf::Uint16 mClient_ServerPort;

	ClientManager mClientManager;
};

}

#endif
