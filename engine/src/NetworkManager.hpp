#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>

#include <boost/foreach.hpp>

#include <SFML/Network.hpp>

//#include "Root.hpp"
#include "Entity.hpp"
#include "ClientManager.hpp"
#include "NetworkCommand.hpp"

namespace Engine {

class NetworkManager {
public:
    NetworkManager();
	//NetworkManager(Root* root);
	~NetworkManager();

	void InitializeAsServer(const sf::Uint16 server_port);
	void InitializeAsClient(const sf::IPAddress server_ip, 
							const sf::Uint16 server_port,
							const std::string name);

    void Receive();
	void HandlePacket(sf::Packet packet, sf::IPAddress address, sf::Uint16 port);

    void PreparePacket();
    void AppendEntityToPacket(Entity& entity);
    void SendPacket(); // TODO: This is not nice!
    void SendPacket(sf::Packet& packet); // This should probably be private 
	// if it is never called like this from the outside. It should also probably
	// be renamed.
    
    // Sends a packet containing NETCMD_CLIENTADD to server / all clients
    void SendClientAdd(const std::string& client_name);

	int GetPing();

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

	// used for calculating pings
	sf::Clock mPingClock;
	sf::Uint16 ping;
};

}

#endif
