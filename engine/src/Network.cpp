#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>

#include <SFML/Network.hpp>

namespace Engine {

class NetworkManager {
public:
	NetworkManager() {}
	~NetworkManager() {}

	void Initialize(sf::Uint16 port);
	void HandleClients();	
	

private:
	sf::SocketUDP Listener;
	sf::SelectorUDP Selector;
	sf::Packet SendPacket;

};

}

#endif
