#include <sstream>

#include "NetworkManager.hpp"
#include "Root.hpp"

namespace Engine {

NetworkManager::NetworkManager() {}
NetworkManager::~NetworkManager() {}

void NetworkManager::InitializeAsServer(const sf::Uint16 server_port){
    mIsServer = true;

	Logger::Debug(LogOrigin::NETWORK, "Initializing NetworkManager as server.");

    if(mListener.Bind(server_port)) {
		Logger::Critical(LogOrigin::NETWORK, "NetworkManager was broken while binding the listening server socket.");
        exit(1);
    } else {
		Logger::Message(LogOrigin::NETWORK, "Binding to port "+boost::lexical_cast<std::string>(server_port)+" successful.");
    }

	int maxplayers = 8;
	mClientManager = ClientManager(maxplayers);

	mListener.SetBlocking(0);

	mReceivedPacketsCount = 0;
	mSentPacketsCount = 0;

	mEntityState = NULL;
	mDuringWorldSnapshot = false;
	mWorldSnapshotWorldUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

void NetworkManager::InitializeAsClient(const sf::IpAddress server_ip, 
										const sf::Uint16 server_port,
										const std::string client_name) {
    mIsServer = false;

	Logger::Debug(LogOrigin::NETWORK, "Initializing NetworkManager as client.");

    mClient_ServerIp = server_ip;
    mClient_ServerPort = server_port;

	mClient_ClientPort = 12357;
	mClient_ClientName = client_name;
	mClient_ConnectedToServer = false;

	mEntityState = NULL;

	mDuringWorldSnapshot = false;
	mWorldSnapshotWorldUniqueId = Root::get_mutable_instance().GetIdManagerPtr()->GetNewUniqueId();
}

void NetworkManager::ConnectToServer() {
	Logger::Debug(LogOrigin::NETWORK, "Start connecting to server.");

	mListener.Bind(mClient_ClientPort);
	mListener.SetBlocking(0);
	mClient_ConnectedToServer = true;

	SendClientAdd(mClient_ClientName);

	mReceivedPacketsCount = 0;
	mSentPacketsCount = 0;
}

void NetworkManager::DisconnectFromServer() {
	mClient_ConnectedToServer = false;
	mListener.Unbind();
}

void NetworkManager::PreparePacket() {
    mPacket.Clear();
}

void NetworkManager::AppendEntityToPacket(Entity& entity) {
	mPacket << sf::Uint16(NETCMD_ENTITYINFO);
	mPacket << entity.GetEntityUniqueId();
	mPacket << entity.GetEntityTypeId();
	Engine::IOPacket p(false, mPacket);
	entity.serialize(p);
	mPacket = p.GetPacket();
}

void NetworkManager::SendPacket() {
	SendPacket(mPacket);
}

void NetworkManager::SendPacket(sf::Packet& packet) {

	// Don't send empty packets.
	if(packet.GetDataSize() == 0) {
		Logger::Warning(LogOrigin::NETWORK, "Won't send empty packet.");
	} else {
		if(mIsServer) {
			// We are sending from server, therefore send to all clients.
			BOOST_FOREACH(sf::Uint16 id, mClientManager.GetIds()) {
				Logger::Debug(LogOrigin::NETWORK, "Sending packet to: "+mClientManager.GetIp(id).ToString()+":"+boost::lexical_cast<std::string>(mClientManager.GetPort(id)));
				mListener.Send(packet, mClientManager.GetIp(id), mClientManager.GetPort(id));
			}
		} else {
			// We are sending from client.
			if(!mClient_ConnectedToServer) {
				Logger::Debug(LogOrigin::NETWORK, "Won't send packet: Client did not connect to server yet.");
			} else {
				Logger::Debug(LogOrigin::NETWORK, "Sending packet to: " + mClient_ServerIp.ToString() + ":" + boost::lexical_cast<std::string>(mClient_ServerPort));
				mListener.Send(packet, mClient_ServerIp, mClient_ServerPort);
			}
		}
		mSentPacketsCount++;
	}
}

void NetworkManager::SendPacket(sf::Packet& packet, sf::Uint16 client_id) {
	// Don't send empty packets.
	if(packet.GetDataSize() == 0) {
		Logger::Warning(LogOrigin::NETWORK, "Won't send empty packet.");
	} else {
		if(mIsServer) {
			Logger::Debug(LogOrigin::NETWORK, "Sending packet to: "+mClientManager.GetIp(client_id).ToString()+":"+boost::lexical_cast<std::string>(mClientManager.GetPort(client_id)));
			mListener.Send(packet, mClientManager.GetIp(client_id), mClientManager.GetPort(client_id));
		} else {
			// WE DONT WANT THAT
			Logger::Warning(LogOrigin::NETWORK, "Won't send packet to a specified client_id from a client. This is the job of the server!");
		}
		mSentPacketsCount++;
	}
}

void NetworkManager::SendClientAdd(const std::string& client_name) {
    sf::Packet packet;
	if(mIsServer) {
		// We don't know our own Id as a client!
		packet << sf::Uint16(NETCMD_CLIENTADD) << client_name << mClientManager.GetId(client_name);
	} else {
		packet << sf::Uint16(NETCMD_CLIENTADD) << client_name;
	}
    SendPacket(packet);
}

void NetworkManager::SendClientQuit(const std::string &reason, const std::string &client_name) {
	sf::Packet packet;
	packet << sf::Uint16(NETCMD_CLIENTQUIT);
	if(mIsServer) {
		packet << client_name << reason;
	}
	SendPacket(packet);

	if(!mIsServer) {
		// unbind socket if client
		DisconnectFromServer();
	}
}

void NetworkManager::SendEntityAdd(Entity& entity, const sf::Uint16 world_unique_id) {
	sf::Packet packet;
	packet << sf::Uint16(NETCMD_ENTITYADD);
	packet << entity.GetEntityTypeId();
	IOPacket iopacket(false, packet);
	entity.serialize(iopacket);
	packet = iopacket.GetPacket();
	SendPacket(packet);
}

void NetworkManager::SendEntityAdd(Entity& entity, const sf::Uint16 client_id, const sf::Uint16 world_unique_id) {
	sf::Packet packet;
	packet << sf::Uint16(NETCMD_ENTITYADD);
	packet << entity.GetEntityTypeId();
	packet << entity.GetEntityTypeId();
	IOPacket iopacket(false, packet);
	entity.serialize(iopacket);
	packet = iopacket.GetPacket();
	SendPacket(packet, client_id);
}

void NetworkManager::SendEntityDel(const sf::Uint16 entity_unique_id, const sf::Uint16 world_unique_id) {
	sf::Packet packet;
	packet << sf::Uint16(NETCMD_ENTITYDEL);
	packet << entity_unique_id;
	packet << world_unique_id;
	SendPacket(packet);
}

void NetworkManager::SendChatMessage(const std::string& chat_message, const std::string& client_name) {
    sf::Packet packet;
    packet << sf::Uint16(NETCMD_CHATMESSAGE);
    if(mIsServer)
        packet << client_name;
    packet << chat_message;
    SendPacket(packet);
}

void NetworkManager::SendPing() {
	if(mIsServer || mClient_ConnectedToServer) {
		mPingClock.Reset();
		sf::Packet packet;
		packet << sf::Uint16(NETCMD_SERVERPING);
		SendPacket(packet);
	}
}

void NetworkManager::SendWorldInfo(sf::Uint16 world_unique_id, sf::Uint16 world_type_id) {
	if(mIsServer) {
		mPacket << sf::Uint16(NETCMD_WORLDINFO_BEGIN);
		mPacket << world_unique_id;
		mPacket << world_type_id;
		GetEntityState()->GetWorld(world_unique_id)->AppendAllEntitiesToPacket();
		mPacket << sf::Uint16(NETCMD_WORLDINFO_END);
		mPacket << world_unique_id;
		SendPacket();
		PreparePacket();
	}
}

void NetworkManager::Receive() {
    if(mIsServer) {
		sf::Packet packet;
		sf::IpAddress client_address;
		sf::Uint16 client_port;

		if(mListener.Receive(packet, client_address, client_port) == sf::Socket::Done) {
			if(mClientManager.IsKnown(client_address, client_port)) {
				sf::Uint16 client_id = mClientManager.GetId(client_address, client_port);
				std::string client_name = mClientManager.GetName(client_id);
				Logger::Debug(LogOrigin::NETWORK, "Received a packet from known client "+client_name+"("+boost::lexical_cast<std::string>(client_address)+":"+boost::lexical_cast<std::string>(client_port)+")");
			} else {
				Logger::Warning(LogOrigin::NETWORK, "Received a packet from unknown client ("+boost::lexical_cast<std::string>(client_address)+":"+boost::lexical_cast<std::string>(client_port)+")");
				if(mClientManager.IsSlotAvailable()) {
					mClientManager.Add(client_address, client_port, "unnamed");
				} else {
					Logger::Urgent(LogOrigin::NETWORK, "No slot available for ("+client_address.ToString()+":"+boost::lexical_cast<std::string>(client_port)+").");
				}
			}

			HandlePacket(packet, client_address, client_port);
			packet.Clear();
		}
    } else {
        sf::Packet packet;
        sf::IpAddress server_address;
        sf::Uint16 server_port;
        
		// TODO: Implement packet queue to handle all sent packets.
		if(mListener.Receive(packet, server_address, server_port) == sf::Socket::Done) {
			Logger::Debug(LogOrigin::NETWORK, "Received a packet from " + boost::lexical_cast<std::string>(server_address) + ":" + boost::lexical_cast<std::string>(server_port));
            HandlePacket(packet, server_address, server_port);
            packet.Clear();
        }
    }
}

void NetworkManager::HandlePacket(sf::Packet& packet, const sf::IpAddress& address, const sf::Uint16 port) {
	// debug message, count NETCMD_ENTITYINFO
	int num_entity_infos = 0;

	mReceivedPacketsCount++;
	Logger::Debug(LogOrigin::NETWORK, "Received packets count: "+boost::lexical_cast<std::string>(mReceivedPacketsCount));

    sf::Uint16 net_cmd;
    while(!packet.EndOfPacket()) {		
        packet >> net_cmd;

        if(mIsServer) {
            // === SERVER PACKET HANDLING ===
			if(net_cmd == NETCMD_EMPTY) {
				Logger::Warning(LogOrigin::NETWORK, "Received NETCMD_EMPTY from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
				exit(1);
			} else if(net_cmd == NETCMD_CLIENTADD) {
				// Fetch name from packet
				std::string client_name;
				packet >> client_name;

				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CLIENTADD from "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");

                // Add new client if unknown
				if(mClientManager.IsKnown(address, port)) {
						// Make a signal here wich is connected to mClientManager.Add() and to MainState.OnClientConnect()
						sf::Uint16 id = mClientManager.GetId(address, port);
						mClientManager.SetName(id, client_name);
						SendClientAdd(client_name);
						TriggerOnClientConnected(id);
						Logger::Message(LogOrigin::NETWORK, "Client "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+") was added successfully.");
				}
			} else if(net_cmd == NETCMD_CLIENTQUIT) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CLIENTQUIT from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                sf::Packet packet;
                sf::Uint16 id = mClientManager.GetId(address, port);
                std::string client_name = mClientManager.GetName(id);
				GetEntityState()->DeleteEntitiesByClientId(id);
					
				if(mClientManager.IsKnown(address, port)) {
					std::string reason = "Lol just quit.";
					SendClientQuit(reason, client_name);
					Logger::Debug(LogOrigin::NETWORK, "Removing "+client_name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");
					mClientManager.Remove(id);
				}
            } else if(net_cmd == NETCMD_CLIENTPING) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CLIENTPING from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                // The client pinged back! 
                // TODO: Calculate the latency.
            } else if(net_cmd == NETCMD_SERVERPING) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_SERVERPING from "+address.ToString()+":"+boost::lexical_cast<std::string>(port));
                // OMG! You got pinged by the client!
                // Just send it back.
                sf::Packet p;
                p << sf::Uint16(NETCMD_SERVERPING);
                SendPacket(p);
            } else if(net_cmd == NETCMD_ENTITYACTION) {
                sf::Uint16 action_id;
                sf::Uint16 entity_unique_id;
                packet >> action_id;
                packet >> entity_unique_id;
                
				Entity* e = GetEntityState()->GetEntityByEntityUniqueId(entity_unique_id);
                if (e != NULL) {
                    sf::Packet response = e->PerformAction(action_id, packet, true);
                    // Send back to all clients.
                    if(response.GetDataSize() > 0) {
                        SendPacket(response);                    
                    }
                }
			} else if(net_cmd == NETCMD_CHATMESSAGE) {
                // Fetch the message
                std::string message;
                packet >> message;
                // Get client name
                sf::Uint16 id = mClientManager.GetId(address, port);
                std::string client_name = mClientManager.GetName(id);
                // Output the message.
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CHATMESSAGE from "+client_name+"("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+")");
				Logger::Message(LogOrigin::NETWORK, "<"+client_name+">: "+message);
                // Send back to everyone
                SendChatMessage(message, client_name);
			} else if(net_cmd == NETCMD_INTERACTION) {
				// Fetch interaction ID
				sf::Uint16 interaction_id;
				sf::Uint16 world_unique_id;
				packet >> interaction_id;
				packet >> world_unique_id;
				GetEntityState()->HandleInteraction(interaction_id, mClientManager.GetId(address, port), world_unique_id, packet);
			} else {
				Logger::Critical(LogOrigin::NETWORK, "Received invalid NETCMD id: "+boost::lexical_cast<std::string>(net_cmd));
				exit(1);
			}
		} else {
            // === CLIENT PACKET HANDLING ===
			if(net_cmd == NETCMD_EMPTY) {
				Logger::Warning(LogOrigin::NETWORK, "Received NETCMD_EMPTY.");
				exit(1);
			} else if(net_cmd == NETCMD_CLIENTADD) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CLIENTADD.");
                // Fetch client name of new client from packet
                std::string client_name;
                packet >> client_name;
                sf::Uint16 client_id;
                packet >> client_id;
                
                // If name is client name of THIS client, then you have beed added
                // successfully to server.
                if (client_name == Root::get_mutable_instance().GetClientName()){
                    Root::get_mutable_instance().SetClientId(client_id);
                }
                // Otherwise, there just was a new client being connected, 
                // so update scoreboard list. 
                // TODO: scoreboard list updating.
                
                TriggerOnClientConnected(client_id);
            } else if(net_cmd == NETCMD_CLIENTPING) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CLIENTPING.");
                // OMG! You got pinged by the server!
                // Just send it back.
				mPingClock.Reset();
                sf::Packet packet;
                packet << sf::Uint16(NETCMD_CLIENTPING);
                SendPacket(packet);
            } else if(net_cmd == NETCMD_SERVERPING) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_SERVERPING.");
                // The server pinged back! 
				mPing = mPingClock.GetElapsedTime() * 1000;
            } else if(net_cmd == NETCMD_ENTITYADD) {
                sf::Uint16 entity_type_id;
                sf::Uint16 world_unique_id;
                packet >> entity_type_id;
                packet >> world_unique_id;
				Entity* entity = Root::get_mutable_instance().GetIdManagerPtr()->
					GetEntityPrototype(entity_type_id);
				entity->Initialize();
				IOPacket iopacket(true, packet);
				entity->serialize(iopacket);
				packet = iopacket.GetPacket();
				GetEntityState()->GetWorld(world_unique_id)->AddEntity(entity);
				Logger::Debug(LogOrigin::NETWORK, "Entity (ID "+boost::lexical_cast<std::string>(entity->GetEntityUniqueId())+") added.");
            } else if(net_cmd == NETCMD_ENTITYACTION) {
                sf::Uint16 action_id;
                sf::Uint16 entity_unique_id;
                packet >> action_id;
                packet >> entity_unique_id;
				Entity* e = GetEntityState()->GetEntityByEntityUniqueId(entity_unique_id);
                e->PerformAction(entity_unique_id, packet, false); // false -> do not validate action, as luckily the server did that for you
			} else if(net_cmd == NETCMD_WORLDINFO_BEGIN) {
				sf::Uint16 world_unique_id;
				packet >> world_unique_id;
				sf::Uint16 world_type_id;
				packet >> world_type_id;
				mDuringWorldSnapshot = true;
				mWorldSnapshotWorldUniqueId = world_unique_id;
				if(GetEntityState()->GetWorld(world_unique_id) == NULL) {
					World* world = Root::get_mutable_instance().GetIdManagerPtr()->
						GetWorldPrototype(world_type_id);
					world->SetWorldUniqueId(world_unique_id);
					GetEntityState()->AddWorld(world);
				}
			} else if(net_cmd == NETCMD_WORLDINFO_END) {
				sf::Uint16 world_unique_id;
				packet >> world_unique_id;
				if(world_unique_id != mWorldSnapshotWorldUniqueId) {
					Logger::Critical(LogOrigin::NETWORK, "Invalid world snapshot received.");
					exit(1);
				}
				mDuringWorldSnapshot = false;
				mWorldSnapshotWorldUniqueId = world_unique_id;
			} else if(net_cmd == NETCMD_ENTITYINFO and mDuringWorldSnapshot) {
				sf::Uint16 entity_unique_id;
                packet >> entity_unique_id;
                
				sf::Uint16 entity_type_id;
				packet >> entity_type_id;

				Entity* e = GetEntityState()->GetWorld(mWorldSnapshotWorldUniqueId)->GetEntityByEntityUniqueId(entity_unique_id);
                if(e != NULL) {
					// Deserialize
					IOPacket iopacket(true, packet);
                    e->serialize(iopacket);
                    packet = iopacket.GetPacket();
					num_entity_infos++;
				} else {
					Logger::Warning(LogOrigin::NETWORK, "Entity with UID "+boost::lexical_cast<std::string>(entity_unique_id)+" not found. Creating new entity.");
					// create new entity
					Entity* entity = Root::get_mutable_instance().GetIdManagerPtr()->
						GetEntityPrototype(entity_type_id);
					entity->Initialize();
					IOPacket iopacket(true, packet);
					entity->serialize(iopacket);
					packet = iopacket.GetPacket();
					GetEntityState()->GetWorld(mWorldSnapshotWorldUniqueId)->AddEntity(entity);
					Logger::Debug(LogOrigin::NETWORK, "Entity (ID "+boost::lexical_cast<std::string>(entity->GetEntityUniqueId())+") added.");
				}
			} else if(net_cmd == NETCMD_ENTITYDEL) {
				sf::Uint16 entity_unique_id;
				packet >> entity_unique_id;
				sf::Uint16 world_unique_id;
				packet >> world_unique_id;
				GetEntityState()->GetWorld(world_unique_id)->DeleteEntityByEntityUniqueId(entity_unique_id);
            } else if(net_cmd == NETCMD_CHATMESSAGE) {
				Logger::Debug(LogOrigin::NETWORK, "Received NETCMD_CHATMESSAGE.");
                // TODO: Output into GUI
                std::string client_name;
                std::string message;
                packet >> client_name;
                packet >> message;
				Logger::Message(LogOrigin::NETWORK, "<"+client_name+">: "+message);
			} else if(net_cmd == NETCMD_CLIENTQUIT) {
				std::string client_name = "";
				std::string reason = "";
				packet >> client_name >> reason;
				Logger::Message(LogOrigin::NETWORK, "Client <"+client_name+"> quit - Reason: " + reason);
			} else {
				Logger::Critical(LogOrigin::NETWORK, "Received invalid NETCMD id: "+boost::lexical_cast<std::string>(net_cmd));
				exit(1);
			}
        }
    }
	// debug message
	if (num_entity_infos > 0)
		Logger::Debug(LogOrigin::NETWORK, "Deserialized "+boost::lexical_cast<std::string>(num_entity_infos)+" x NETCMD_ENTITYINFO.");
}

void NetworkManager::BindOnClientConnected(const boost::signals2::signal<void (const sf::Uint16)>::slot_type& slot) {
    mOnClientConnectedSignal.connect(slot);
}
void NetworkManager::TriggerOnClientConnected(const sf::Uint16 client_id) {
    mOnClientConnectedSignal(client_id);
}

sf::Uint16 NetworkManager::GetPing() {
	return mPing;
}

ClientManager* NetworkManager::GetClientManagerPtr() {
	return &mClientManager;
}

void NetworkManager::SetServerIp(const sf::IpAddress server_ip) {
	mClient_ServerIp = server_ip;
}

const sf::IpAddress NetworkManager::GetServerIp() {
	return mClient_ServerIp;
}

void NetworkManager::SetServerPort(const sf::Uint16 server_port) {
	mClient_ServerPort = server_port;
}

sf::Uint16 NetworkManager::GetServerPort() {
	return mClient_ServerPort;
}

void NetworkManager::SetEntityState(State* entity_state) {
	mEntityState = entity_state;
}

State* NetworkManager::GetEntityState() {
	if(mEntityState == NULL) {
		Logger::Critical(LogOrigin::NETWORK, "No Entity State specified, but requested. Quitting.");
		exit(1);
	}
	return mEntityState;
}

void NetworkManager::SetClientName(const std::string& client_name) {
	mClient_ClientName = client_name;
}

std::string NetworkManager::GetClientName() {
	return mClient_ClientName;
}

}
