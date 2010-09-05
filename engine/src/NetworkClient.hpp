#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP


#include "Entity.hpp"
#include "NetworkManager.hpp"

namespace Engine {

class NetworkClient : public NetworkManager {
public:
	void SendEntity(Entity* ent);
};

}

#endif
