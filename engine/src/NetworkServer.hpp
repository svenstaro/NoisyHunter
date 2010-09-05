#ifndef NETWORKSERVER_HPP
#define NETWORKSERVER_HPP

#include "NetworkManager.hpp"
#include "Definitions.hpp"
#include <SFML/Network.hpp>

namespace Engine {

class NetworkServer : public NetworkManager {

public:
	void Initialize(const sf::Uint16 port);
	void HandleClients();
private:
	sf::SelectorUDP mSelector;
};

}

#endif
