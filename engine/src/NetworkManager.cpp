#include "NetworkManager.hpp"

#include <boost/archive/binary_oarchive.hpp>
#include <sstream>

namespace Engine {

NetworkManager::NetworkManager() {}
/*NetworkManager::NetworkManager(Root* root) {
    mRoot = root;
}*/
NetworkManager::~NetworkManager() {}

void NetworkManager::InitializeAsServer(const sf::Uint16 server_port){
    mIsServer = true;

    if (!mListener.Bind(server_port)) {
        std::cerr << "[NETWORK/SERVER] NetworkManager was broken while binding the listening SERVER socket." << std::endl;
        exit(1);
    }
    else{
        std::cout << "[SERVER] Binding to port " << server_port << " successful." << std::endl;
    }

    mServer_Selector.Add(mListener);
	mClientManager = ClientManager(2);

	mListener.SetBlocking(1);
}


void NetworkManager::InitializeAsClient(const sf::IPAddress server_ip, const sf::Uint16 server_port) {
    mIsServer = false;

    mClient_ServerIp = server_ip;
    mClient_ServerPort = server_port;


	/*
    if (!mListener.Bind(client_port)) {
        std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
        exit(1);
    }
	*/

    // TODO: Handshake
}

void NetworkManager::PreparePacket(){
    mPacket.Clear();
}

void NetworkManager::AddEntity(Entity& entity){
    std::ostringstream os;
    boost::archive::binary_oarchive oa(os, boost::archive::no_header);
    oa << entity;
	mPacket << entity.GetEntityId();
    mPacket << os.str();
}

void NetworkManager::SendPacket(){
    if (mIsServer){
		BOOST_FOREACH(sf::Uint16 id, mClientManager.GetIDs()) {
			mListener.Send(mPacket, mClientManager.GetIP(id), mClientManager.GetPort(id));
		}
    }
    else{
        mListener.Send(mPacket, mClient_ServerIp, mClient_ServerPort);
    }


}

void NetworkManager::HandleClients() {
    if (!mIsServer) {
        std::cerr << "[NETWORK/CLIENT] Client cannot execute server methods." << std::endl;
        exit(1);
    }
    else {
		std::cout << "[NETWORK/SERVER] Server::HandleClients()" << std::endl;
        unsigned int nb_sockets = mServer_Selector.Wait();

        for (unsigned int i=0;i < nb_sockets; ++i) {
            sf::SocketUDP socket = mServer_Selector.GetSocketReady(i);

			sf::Packet packet;
			sf::IPAddress client_address;
			sf::Uint16 client_port;

			if (socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
				std::cout << "[NETWORK/SERVER] Received a packet" << std::endl;
				sf::Uint16 x;
				sf::Uint16 y;
				packet >> x >> y;
				std::cout << "[NETWORK/SERVER] Client says: \"" << x << " - " << y << "\"" << std::endl << std::endl;
				packet.Clear();
				// TODO: Handle client later here
            }
        }
    }
}


}
