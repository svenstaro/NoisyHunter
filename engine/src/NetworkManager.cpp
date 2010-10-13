#include <sstream>

#include "NetworkManager.hpp"
#include "Root.hpp"

namespace Engine {

NetworkManager::NetworkManager() {}
NetworkManager::~NetworkManager() {}

void NetworkManager::InitializeAsServer(const sf::Uint16 server_port){
    mIsServer = true;

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Initializing NetworkManager as server.");

    if(!mListener.Bind(server_port)) {
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_NETWORK, "NetworkManager was broken while binding the listening server socket.");
        exit(1);
    } else {
		logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Binding to port "+boost::lexical_cast<std::string>(server_port)+" successful.");
    }

    mServer_Selector.Add(mListener);
	mClientManager = ClientManager(2);

	mListener.SetBlocking(1);
}

void NetworkManager::InitializeAsClient(const sf::IPAddress server_ip, 
										const sf::Uint16 server_port,
										const std::string client_name) {
    mIsServer = false;

	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Initializing NetworkManager as client.");

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
	// Don't send empty packets.
	if(packet.GetDataSize() == 0) {
		auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
		logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_NETWORK, "Won't send empty packet.");
	} else {
		if(mIsServer) {
			// We are sending from server, therefore send to all clients.
			BOOST_FOREACH(sf::Uint16 id, mClientManager.GetIds()) {
				mListener.Send(packet, mClientManager.GetIp(id), mClientManager.GetPort(id));
			}
		} else {
			// We are sending from client.
			mListener.Send(packet, mClient_ServerIp, mClient_ServerPort);
		}
	}
}

void NetworkManager::SendClientAdd(const std::string& client_name) {
    sf::Packet packet;
    packet << sf::Uint16(NETCMD_CLIENTADD) << client_name;
    SendPacket(packet);
}

void NetworkManager::SendEntityAdd(Entity* entity) {
	sf::Packet packet;
	packet << sf::Uint16(NETCMD_ENTITYADD);
	packet << entity->GetEntityId();
	IOPacket iopacket(false, packet);
	entity->serialize(iopacket);
	packet = iopacket.GetPacket();
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
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

    if(mIsServer) {
		logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Receiving.");
        unsigned int nb_sockets = mServer_Selector.Wait(0.5f);

        for(unsigned int i=0;i < nb_sockets; ++i) {
            sf::SocketUDP socket = mServer_Selector.GetSocketReady(i);

			sf::Packet packet;
			sf::IPAddress client_address;
			sf::Uint16 client_port;

			// TODO: Implement packet queue to handle all sent packets.
			if(socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
				sf::Uint16 client_id = mClientManager.GetId(client_address);
				std::string client_name = mClientManager.GetName(client_id);
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received a packet from "+client_name+"("+boost::lexical_cast<std::string>(client_address)+":"+boost::lexical_cast<std::string>(client_port)+")");
				HandlePacket(packet, client_address, client_port);
				packet.Clear();
            }
        }
    } else {
        sf::Packet packet;
        sf::IPAddress server_address;
        sf::Uint16 server_port;
        
			// TODO: Implement packet queue to handle all sent packets.
        if(mListener.Receive(packet, server_address, server_port) == sf::Socket::Done){
			sf::Uint16 client_id = mClientManager.GetId(server_address);
			logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received a packet from "+boost::lexical_cast<std::string>(server_address)+":"+boost::lexical_cast<std::string>(server_port));
            HandlePacket(packet, server_address, server_port);
            packet.Clear();
        }
    }
}

void NetworkManager::HandlePacket(sf::Packet& packet, const sf::IPAddress& address, const sf::Uint16 port) {
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();

    sf::Uint16 net_cmd;
    while(!packet.EndOfPacket()) {
        packet >> net_cmd;
        
        if(mIsServer) {
            // === SERVER PACKET HANDLING ===
			if(net_cmd == NETCMD_EMPTY) {
				logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_NETWORK, "Received NETCMD_EMPTY from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
				exit(1);
			} else if(net_cmd == NETCMD_CLIENTADD) {
				// Fetch name from packet
				std::string client_name;
				packet >> client_name;

				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTADD from "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");

                // Add new client if unknown
				if(!mClientManager.IsKnown(address)) {
					if(mClientManager.IsSlotAvailable()) {
						// Make a signal here wich is connected to mClientManager.Add() and to MainState.OnClientConnect()
						mClientManager.Add(address, port, client_name);
                        OnClientConnected(client_name);
						SendClientAdd(client_name);
						
						logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "Client "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+") was added successfully.");
					} else {
						logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "No slot available for "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+").");
					}
				}
			} else if(net_cmd == NETCMD_CLIENTQUIT) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTQUIT from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                sf::Packet packet;
                sf::Uint16 id = mClientManager.GetId(address);
                std::string client_name = mClientManager.GetName(id);
				if(mClientManager.IsKnown(address)) {
					logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "Removing "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");
					mClientManager.Remove(id);
				}

				// TODO: Notify other clients of client quit.
                //packet << sf::Uint16(NETCMD_CLIENTQUIT);
				//packet << client_name;
				//packet << "REASON: LOL";
                //SendPacket(packet);
            } else if(net_cmd == NETCMD_CLIENTPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CLIENTPING from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                // The client pinged back! 
                // TODO: Calculate the latency.
            } else if(net_cmd == NETCMD_SERVERPING) {
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_SERVERPING from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                // OMG! You got pinged by the server!
                // Just send it back.
                sf::Packet p;
                p << sf::Uint16(NETCMD_SERVERPING);
                SendPacket(p);
            } else if(net_cmd == NETCMD_ENTITYACTION) {
                sf::Uint16 action_id;
                sf::Uint16 unique_id;
                packet >> action_id;
                packet >> unique_id;
                
                // TODO: Add the entities and synchronize their Unique IDs so you can get the correct entity
                // Entity* e = Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityByUniqueId(unique_id);
                // sf::Packet response = e->PerformAction(action_id, packet, true);
                // Send back to all clients.
                // if(response.GetDataSize() > 0) {
                //     SendPacket(response);                    
                // }
			} else if(net_cmd == NETCMD_CHATMESSAGE) {
                // Fetch the message
                std::string message;
                packet >> message;
                // Get client name
                sf::Uint16 id = mClientManager.GetId(address);
                std::string client_name = mClientManager.GetName(id);
                // Output the message.
				logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Received NETCMD_CHATMESSAGE from "+client_name+"("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");
				logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, client_name+" says: "+message);
                // Send back to everyone
                SendChatMessage(message, client_name);
			}
		} else {
            // === CLIENT PACKET HANDLING ===
			if(net_cmd == NETCMD_EMPTY) {
				logmgr->Log(LOGLEVEL_ERROR, LOGORIGIN_NETWORK, "Received NETCMD_EMPTY.");
				exit(1);
			} else if(net_cmd == NETCMD_CLIENTADD) {
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
            } else if(net_cmd == NETCMD_ENTITYADD) {
                sf::Uint16 entity_id;
                packet >> entity_id;
				Entity* entity = Root::get_mutable_instance().GetIdManagerPtr()->
					GetEntityPrototype(entity_id);
				entity->Initialize();
				IOPacket iopacket(true, packet);
				entity->serialize(iopacket);
				packet = iopacket.GetPacket();
                Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().AddEntity(entity);
            } else if(net_cmd == NETCMD_ENTITYACTION) {
                sf::Uint16 action_id;
                sf::Uint16 unique_id;
                packet >> action_id;
                packet >> unique_id;
                Entity* e = Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityByUniqueId(unique_id);
                e->PerformAction(unique_id, packet, false); // false -> do not validate action, as luckily the server did that for you
            } else if(net_cmd == NETCMD_ENTITYINFO) {
				// FINISH IMPLEMENTATION
                sf::Uint16 entity_id;
                packet >> entity_id;
                //Entity* e = Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityByUniqueId(unique_id);
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

ClientManager* NetworkManager::GetClientManagerPtr() {
	return &mClientManager;
}

}
