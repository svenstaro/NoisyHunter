#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/signals2.hpp>

#include <SFML/Network.hpp>

#include "Entity.hpp"
#include "State.hpp"
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
	void InitializeAsClient(const sf::IpAddress server_ip, 
							const sf::Uint16 server_port,
							const std::string name);

	void ConnectToServer();

    // Receiving methods
    void Receive();
	void HandlePacket(sf::Packet& packet, const sf::IpAddress& address, const sf::Uint16 port);

    // Sending methods
    void PreparePacket();
    void AppendEntityToPacket(Entity& entity);
    // Sends the prepared packet "mPacket" by calling SendPacket(mPacket).
    void SendPacket();
    void SendPacket(sf::Packet& packet);
	void SendPacket(sf::Packet& packet, sf::Uint16 client_id);

	// Sends a packet containing NETCMD_CLIENTADD to server / all clients.
	void SendClientAdd(const std::string& client_name);

	// Sends a packet containing NETCMD_CLIENTQUIT to server / all clients.
	void SendClientQuit(const std::string& reason = "", const std::string& client_name = "");

    // Sends a packet containing NETCMD_ENTITYADD to server / all clients.
	void SendEntityAdd(Entity& entity);
	void SendEntityAdd(Entity& entity, const sf::Uint16 client_id);

	// Sends a packet containgin NETCMD_ENTITYADD to all clients.
	void SendEntityDel(const sf::Uint16 unique_id);

	// Sends a packet which requests a ping response; In a way PONG :D
	void SendPing();

    // Sends a packet containing NETCMD_CHATMESSAGE to server / all clients.
    void SendChatMessage(const std::string& chat_message, const std::string& client_name = "");
    
    // Signal binding & events
    void BindOnClientConnected(const boost::signals2::signal<void (const sf::Uint16)>::slot_type& slot);
    void TriggerOnClientConnected(const sf::Uint16 client_id);

	sf::Uint16 GetPing();

	ClientManager* GetClientManagerPtr();

	void SetServerIp(const sf::IpAddress server_ip);
	const sf::IpAddress GetServerIp();

	void SetServerPort(const sf::Uint16 server_port);
	const sf::Uint16 GetServerPort();

	void SetEntityState(State* entity_state);
	State* GetEntityState();

	void SetClientName(const std::string& client_name);
	std::string GetClientName();

private:
	// General members
    bool mIsServer;
	sf::UdpSocket mListener;
	sf::Packet mPacket;

    // Members used when in server mode
	ClientManager mClientManager;
    
    // Members used when in client mode
    sf::IpAddress mClient_ServerIp;
    sf::Uint16 mClient_ServerPort;
    sf::Uint16 mClient_ClientPort;
	std::string mClient_ClientName;
	bool mClient_ConnectedToServer;
	State* mEntityState;

    // Signals
    boost::signals2::signal<void (const sf::Uint16)> mOnClientConnectedSignal;

	// Used for calculating pings
	sf::Clock mPingClock;
	sf::Uint16 mPing;

	sf::Uint32 mReceivedPacketsCount;
	sf::Uint32 mSentPacketsCount;

	sf::Clock mTimeOutClock;
};

}

#endif
