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

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
    if(!mListener.Bind(server_port)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_NETWORK, "NetworkManager was broken while binding the listening server socket.");
        exit(1);
    } else {
		logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Binding to port "+server_port+" successful.");
    }

    mServer_Selector.Add(mListener);
	mClientManager = ClientManager(2);

	mListener.SetBlocking(1);
}

void NetworkManager::InitializeAsClient(const sf::IPAddress server_ip, 
										const sf::Uint16 server_port,
										const std::string client_name) {
    mIsServer = false;

    mClient_ServerIp = server_ip;
    mClient_ServerPort = server_port;

    mClient_ClientPort = 12357;
    mListener.Bind(mClient_ClientPort);
    mListener.SetBlocking(0);
    
	SendClientAdd(client_name);
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
		logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Receiving.");
        unsigned int nb_sockets = mServer_Selector.Wait();

        for (unsigned int i=0;i < nb_sockets; ++i) {
            sf::SocketUDP socket = mServer_Selector.GetSocketReady(i);

			sf::Packet packet;
			sf::IPAddress client_address;
			sf::Uint16 client_port;

			if(socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received a packet from "+client_address+":"+client_port);
				HandlePacket(packet, client_address, client_port);
				packet.Clear();
            }
        }
    } else {
        sf::Packet packet;
        sf::IPAddress server_address;
        sf::Uint16 server_port;
        
        if (mListener.Receive(packet, server_address, server_port) == sf::Socket::Done){
			logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received a packet from "+server_address+":"+server_port);
            HandlePacket(packet, server_address, server_port);
            packet.Clear();
        }
    }
}

void NetworkManager::HandlePacket(sf::Packet& packet, const sf::IPAddress& address, const sf::Uint16 port) {
    sf::Uint16 net_cmd;
    while(!packet.EndOfPacket()) {
        packet >> net_cmd;
        
        if(mIsServer) {
            // === SERVER PACKET HANDLING ===
            if(net_cmd == NETCMD_CLIENTADD) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTADD.");
                // Fetch name from packet
				std::string client_name;
				packet >> client_name;
                // Add new client if unknown
				if(!mClientManager.IsKnown(address)) {
					if(mClientManager.IsSlotAvailable()) {
						// Make a signal here wich is connected to mClientManager.Add() and to MainState.OnClientConnect()
						mClientManager.Add(address, port, client_name);
                        OnClientConnected(client_name);
						SendClientAdd(client_name);
						
						logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "Client "+client_name+" was added successfully.");
					} else {
						logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "No slot available.");
					}
				}
			} else if(net_cmd == NETCMD_CLIENTQUIT) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTQUIT.");
                sf::Packet packet;
                sf::Uint16 id = mClientManager.GetId(address);
                std::string client_name = mClientManager.GetName(id);
                packet << sf::Uint16(NETCMD_CLIENTQUIT);
				packet << client_name;
				packet << "REASON: LOL";
                SendPacket(packet);
            } else if(net_cmd == NETCMD_CLIENTPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTPING.");
                // The client pinged back! 
                // TODO: Calculate the latency.
            } else if(net_cmd == NETCMD_SERVERPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_SERVERPING.");
                // OMG! You got pinged by the server!
                // Just send it back.
                sf::Packet packet;
                packet << sf::Uint16(NETCMD_SERVERPING);
                SendPacket(packet);
			} else if(net_cmd == NETCMD_CHATMESSAGE) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CHATMESSAGE.");
                // Fetch the message
                std::string message;
                packet >> message;
                // Get client name
                sf::Uint16 id = mClientManager.GetId(address);
                std::string client_name = mClientManager.GetName(id);
                // Output the message.
				logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, client_name+" says: "+message);
                // Send back to everyone
                SendChatMessage(message, client_name);
			}
		} else {
            // === CLIENT PACKET HANDLING ===
            if(net_cmd == NETCMD_CLIENTADD) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTADD.");
                // Fetch client name of new client from packet
                std::string client_name;
                packet >> client_name;
                // If name is client name of THIS client, then you have beed added
                // successfully to server.
                // Otherwise, there just was a new client being connected, 
                // so update scoreboard list. (TODO: scoreboard list updating)
                OnClientConnected(client_name);
            } else if(net_cmd == NETCMD_CLIENTPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTPING.");
                // OMG! You got pinged by the server!
                // Just send it back.
				mPingClock.Reset();
                sf::Packet packet;
                packet << sf::Uint16(NETCMD_CLIENTPING);
                SendPacket(packet);
            } else if(net_cmd == NETCMD_SERVERPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_SERVERPING.");
                // The server pinged back! 
				mPing = mPingClock.GetElapsedTime() * 1000;
            } else if(net_cmd == NETCMD_CHATMESSAGE) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CHATMESSAGE.");
                // TODO: Output into GUI
                std::string client_name;
                std::string message;
                packet >> client_name;
                packet >> message;
				logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, client_name+" says: "+message);
            }
        }
    }
}

void NetworkManager::BindOnClientConnected(const boost::signals2::signal<void (const std::string&)>::slot_type& slot) {
    mOnClientConnectedSignal.connect(slot);
}
void NetworkManager::OnClientConnected(const std::string& client_name) {
    mOnClientConnectedSignal(client_name);
}

sf::Uint16 NetworkManager::GetPing() {
	return mPing;
}

}
