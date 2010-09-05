#include "NetworkClient.hpp"

namespace Engine {

class NetworkClient {

public:
	void SendEntity(Engine::Entity* ent) {
	
		sf::Uint16 x = ent->Position.x;
		sf::Uint16 y = ent->Position.y;

		SendPacket << x << y;
		Listener.Send(SendPacket, "127.0.0.1", 12345);
		SendPacket.Clear();
	
	}

}

}
