#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>

#include <SFML/Network.hpp>

#include "Entity.hpp"
#include "ClientManager.hpp"
#include "NetworkCommand.hpp"
#include "LogManager.hpp"
#include "IdManager.hpp"

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
	void HandlePacket(sf::Packet& packet, const sf::IPAddress& address, const sf::Uint16 port);

    // Sending methods
    void PreparePacket();
    void AppendEntityToPacket(Entity& entity);
    // Sends the prepared packet "mPacket" by calling SendPacket(mPacket).
    void SendPacket();
    void SendPacket(sf::Packet& packet);
    
    // Sends a packet containing NETCMD_CLIENTADD to server / all clients.
    void SendClientAdd(const std::string& client_name);

    // Sends a packet containing NETCMD_CHATMESSAGE to server / all clients.
    void SendChatMessage(const std::string& chat_message, const std::string& client_name = "");
    
    // Signal binding & events
    void BindOnClientConnected(const boost::signals2::signal<void (const std::string&)>::slot_type& slot);
    void OnClientConnected(const std::string& client_name);


	sf::Uint16 GetPing();
private:
    // General members
    bool mIsServer;
	sf::SocketUDP mListener;
	sf::Packet mPacket;

    // Members used when in server mode
	sf::SelectorUDP mServer_Selector;

    // Members used when in client mode
    sf::IPAddress mClient_ServerIp;
    sf::Uint16 mClient_ServerPort;
    sf::Uint16 mClient_ClientPort;

	ClientManager mClientManager;
    
    // Signals
    boost::signals2::signal<void (const std::string&)> mOnClientConnectedSignal;

	// Used for calculating pings
	sf::Clock mPingClock;
	sf::Uint16 mPing;
};

}

#endif
