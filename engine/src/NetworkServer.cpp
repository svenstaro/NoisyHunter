#include "NetworkServer.hpp"

namespace Engine {

	NetworkServer::Initialize(const sf::Uint16 port) {
	
		if (!Listener.Bind(port)) {
			std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
			exit(1);
		}
	
		Selector.Add(Listener);

	}

	NetworkManager::HandleClients() {
	
		unsigned int NBSockets = Selector.Wait();

		for (unsigned int i=0;i < NBSockets; ++i) {
		
			sf::SocketUDP Socket = Selector.GetSocketReady(i);

			if (Socket == Listener) {
			
				sf::IPAddress Address;
				sf::SocketUDP Client;
				std::cout << "[NETWORK] Your penis shots out a client from [" << Address << "]." << std::endl;

				Selector.Add(Client);

			} else { // Handle a connected client
			 
				sf::Packet Packet;

				if (Socket.Receive(Packet) == sf::Socket::Done) {
					sf::Uint16 x;
					sf::Uint16 y;
					Packet >> x >> y;
					std::cout << "Your penis looks quite interested at you and says :\"" << x << y << "\"" << std::endl;
					Packet.Clear();
					// TODO: Handle client later here
				} else {
				
					Selector.Remove(Socket);
				
				}
			 
			}
		
		}
	}	
}
