#include "NetworkManager.hpp"

namespace Engine {

	NetworkManager::Initialize(sf::Uint16 port) {

		if (!Listener.Bind(port)) {
			std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
			exit(1);
		}
		
	}

}
