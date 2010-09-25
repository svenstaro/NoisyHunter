#include <sstream>

#include <boost/archive/binary_oarchive.hpp>

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
										const sf::Uint16 server_port) {
    mIsServer = false;

    mClient_ServerIp = server_ip;
    mClient_ServerPort = server_port;

	/*
    if(!mListener.Bind(client_port)) {
        std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
        exit(1);
    }
	*/

    // TODO: Handshake
}

void NetworkManager::PreparePacket() {
    mPacket.Clear();
}

void NetworkManager::AddEntity(Entity& entity) {
    mPacket << entity.GetEntityId();
    Engine::IOPacket p(true,mPacket);
    entity.serialize(p);
    mPacket = p.GetPacket();
}

void NetworkManager::SendPacket() {
    SendPacket(mPacket);
}

void NetworkManager::SendPacket(const sf::Packet& packet) {
    if(mIsServer) {
		BOOST_FOREACH(sf::Uint16 id, mClientManager.GetIDs()) {
			mListener.Send(packet, mClientManager.GetIP(id), mClientManager.GetPort(id));
		}
    } else {
        mListener.Send(packet, mClient_ServerIp, mClient_ServerPort);
    }
}

void NetworkManager::SendClientAdd(const std::string& client_name) {
    sf::Packet packet;
    packet << sf::Uint16(NETCMD_CLIENTADD) << client_name;
    SendPacket(packet);
}

void NetworkManager::HandleClients() {
    if(!mIsServer) {
        std::cerr << "[NETWORK/CLIENT] Client cannot execute server methods." << std::endl;
        exit(1);
    } else {
		std::cout << "[NETWORK/SERVER] Server::HandleClients()" << std::endl;
        unsigned int nb_sockets = mServer_Selector.Wait();

        for (unsigned int i=0;i < nb_sockets; ++i) {
            sf::SocketUDP socket = mServer_Selector.GetSocketReady(i);

			sf::Packet packet;
			sf::IPAddress client_address;
			sf::Uint16 client_port;

			if(socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
				std::cout << "[NETWORK/SERVER] Received a packet" << std::endl;
				HandlePacket(packet);
				packet.Clear();
            }
        }
    }
}

void NetworkManager::HandlePacket(sf::Packet packet, sf::IPAddress address, sf::Uint16 port) {
	if(!mIsServer) {
		// TODO: Actually do stuff here.
	} else {
		sf::Uint16 net_cmd;
		while(!packet.EndOfPacket()) {
			packet >> net_cmd;
			if(net_cmd == NETCMD_CLIENTADD) {
				std::string name;
				packet >> name;

				if(!mClientManager.IsKnown(address)) {

					if(mClientManager.IsSlotAvailable()) {
						mClientManager.Add(address, port, name); 
						SendClientAdd(name);
						std::cout << "[NETWORK/SERVER] Client [" + name + "] was added successfully."
					} else {
						std::cerr << "[NETWORK/SERVER] No slot available." << std::endl;
					}
				}

			}

			if(net_cmd == NETCMD_ENTITYINFO) {
				Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().HandleEntityInfo(packet);
			}
		}
	}
}

}
