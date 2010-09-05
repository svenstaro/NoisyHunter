#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <iostream>

#include <SFML/Network.hpp>

namespace Engine {

class NetworkManager {
public:
	NetworkManager() {}
	~NetworkManager() {}

	virtual void Initialize(const sf::Uint16 port);


protected:
	sf::SocketUDP Listener;
	sf::Packet SendPacket;

};

}

#endif
