#ifndef NETWORKCLIENT
#define NETWORKCLIENT


#include "Entity.hpp"
#include "NetworkManager.hpp"

namespace Engine {

class NetworkClient : public NetworkManager {

public:
	void SendEntitiy(Engine::Entity* ent);

}

}

#endif
