#include <sstream>

#include "NetworkManager.hpp"
#include "Root.hpp"

namespace Engine {

NetworkManager::NetworkManager() {}
/*NetworkManager::NetworkManager(Root* root) {
    mRoot = root;
}*/
NetworkManager::~NetworkManager() {}

void NetworkManager::InitializeAsServer(const sf::Uint16 server_port){
    mIsServer = true;

    if(!mListener.Bind(server_port)) {
        std::cerr << "[NETWORK/SERVER] NetworkManager was broken while binding the listening SERVER socket." << std::endl;
        exit(1);
    } else {
        std::cout << "[SERVER] Binding to port " << server_port << " successful." << std::endl;
    }

    mServer_Selector.Add(mListener);
	mClientManager = ClientManager(2);

	mListener.SetBlocking(1);
}

void NetworkManager::InitializeAsClient(const sf::IPAddress server_ip, 
										const sf::Uint16 server_port,
										const std::string name) {
    mIsServer = false;

    mClient_ServerIp = server_ip;
    mClient_ServerPort = server_port;

	/*
    if(!mListener.Bind(client_port)) {
        std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
        exit(1);
    }
	*/

	SendClientAdd(name);	
}

void NetworkManager::PreparePacket() {
    mPacket.Clear();
}

void NetworkManager::AppendEntityToPacket(Entity& entity) {
    mPacket << entity.GetEntityId();
    Engine::IOPacket p(true,mPacket);
    entity.serialize(p);
    mPacket = p.GetPacket();
}

void NetworkManager::SendPacket() {
	SendPacket(mPacket);
}

void NetworkManager::SendPacket(sf::Packet& packet) {
	if(mIsServer) {
		BOOST_FOREACH(sf::Uint16 id, mClientManager.GetIds()) {
			mListener.Send(packet, mClientManager.GetIp(id), mClientManager.GetPort(id));
		}
    } else {
		if(packet.GetDataSize() > 2) {
			mListener.Send(packet, mClient_ServerIp, mClient_ServerPort);
		}
    }
}

void NetworkManager::SendClientAdd(const std::string& client_name) {
    sf::Packet packet;
    packet << sf::Uint16(NETCMD_CLIENTADD) << client_name;
    SendPacket(packet);
}

void NetworkManager::SendChatMessage(const std::string& chat_message, const std::string& client_name) {
    sf::Packet packet;
    packet << sf::Uint16(NETCMD_CHATMESSAGE);
    if (mIsServer)
        packet << client_name;
    packet << chat_message;
    SendPacket(packet);
}

void NetworkManager::Receive() {
    if(mIsServer) {
		std::cout << "[NETWORK/SERVER] Server::HandleClients()" << std::endl;
        unsigned int nb_sockets = mServer_Selector.Wait();

        for (unsigned int i=0;i < nb_sockets; ++i) {
            sf::SocketUDP socket = mServer_Selector.GetSocketReady(i);

			sf::Packet packet;
			sf::IPAddress client_address;
			sf::Uint16 client_port;

			if(socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
				std::cout << "[NETWORK/SERVER] Received a packet from " << client_address << ":" << client_port << std::endl;
				HandlePacket(packet, client_address, client_port);
				packet.Clear();
            }
        }
    } else {
        // TODO: Client receiving        
    }
}

void NetworkManager::HandlePacket(sf::Packet packet, sf::IPAddress address, sf::Uint16 port) {
    sf::Uint16 net_cmd;
    while(!packet.EndOfPacket()) {
        packet >> net_cmd;
        
        if(mIsServer) {
            // Server packet handling
            if(net_cmd == NETCMD_CLIENTADD) {
                // Fetch name from packet
				std::string name;
				packet >> name;
                // Add new client if unknown
				if(!mClientManager.IsKnown(address)) {
					if(mClientManager.IsSlotAvailable()) {
						// Make a signal here wich is connected to mClientManager.Add() and to MainState.OnClientConnect()
						mClientManager.Add(address, port, name); 
						SendClientAdd(name);
						

						std::cout << "[NETWORK/SERVER] Client [" + name + "] was added successfully." << std::endl;
					} else {
						std::cerr << "[NETWORK/SERVER] No slot available." << std::endl;
					}
				}
			} else if(net_cmd == NETCMD_CHATMESSAGE) {
                // Fetch the message
                std::string msg;
                packet >> msg;
                // Get username
                sf::Uint16 id = mClientManager.GetId(address);
                std::string name = mClientManager.GetName(id);
                // Output the message.
                std::cout << "<" << name << "> [" << address << ":" << port << "] said: " << msg << std::endl;
                // Send back to everyone
                SendChatMessage(msg, name);
            } else if(net_cmd == NETCMD_CLIENTPING) {
                // The client pinged back! 
                // TODO: Calculate the latency.
            } else if(net_cmd == NETCMD_SERVERPING) {
                // OMG! You got pinged by the server!
                // Just send it back.
                sf::Packet p;
                p << sf::Uint16(NETCMD_SERVERPING);
                SendPacket(p);
            }
		} else {
            // Client packet handling
            if(net_cmd == NETCMD_CLIENTADD) {
                // Fetch username of new client from packet
                std::string name;
                packet >> name;
                // If name is username of THIS client, then you have beed added
                // successfully to server.
                // Otherwise, there just was a new client being connected, 
                // so update scoreboard list.
            } else if(net_cmd == NETCMD_CLIENTPING) {
                // OMG! You got pinged by the server!
                // Just send it back.
				mPingClock.Reset();
                sf::Packet p;
                p << sf::Uint16(NETCMD_CLIENTPING);
                SendPacket(p);
            } else if(net_cmd == NETCMD_SERVERPING) {
                // The server pinged back! 
				mPing = mPingClock.GetElapsedTime() * 1000;
            } else if(net_cmd == NETCMD_CHATMESSAGE) {
                // TODO: Output into GUI
                std::string username;
                std::string message;
                packet >> username;
                packet >> message;
                std::cout << "<" << username << ">: " << message << std::endl;
            }
        }
        
        
    }
}

sf::Uint16 NetworkManager::GetPing() {
	return mPing;
}

}
