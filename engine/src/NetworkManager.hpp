#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>

#include <boost/foreach.hpp>

#include <SFML/Network.hpp>

#include "Entity.hpp"
#include "ClientManager.hpp"
#include "NetworkCommand.hpp"

namespace Engine {

class NetworkManager {
public:
    NetworkManager();
	~NetworkManager();

	void InitializeAsServer(const sf::Uint16 server_port);
	void InitializeAsClient(const sf::IPAddress server_ip, 
							const sf::Uint16 server_port,
							const std::string name);

    // Receiving methods
    void Receive();
	void HandlePacket(sf::Packet packet, sf::IPAddress address, sf::Uint16 port);

    // Sending methods
    void PreparePacket();
    void AppendEntityToPacket(Entity& entity);
    // Sends the prepared packet "mPacket" by calling SendPacket(mPacket);
    void SendPacket();
    void SendPacket(sf::Packet& packet);
    
    // Sends a packet containing NETCMD_CLIENTADD to server / all clients
    void SendClientAdd(const std::string& client_name);

    // Sends a packet containing NETCMD_CHATMESSAGE to server / all clients
    void SendChatMessage(const std::string& chat_message, const std::string& client_name = "");


	sf::Uint16 GetPing();
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
	sf::Uint16 mPing;
};

}

#endif
