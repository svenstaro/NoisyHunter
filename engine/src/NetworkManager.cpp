#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>

#include <SFML/Network.hpp>

namespace Engine {

class NetworkManager {
public:
	NetworkManager() {}
	~NetworkManager() {}

	virtual void Initialize(const sf::Uint16 port);
	

private:
	sf::SocketUDP Listener;
	sf::Packet SendPacket;

};

}

#endif
