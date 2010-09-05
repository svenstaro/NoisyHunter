#include "NetworkClient.hpp"

namespace Engine {

void NetworkClient::SendEntity(Entity* ent) {
    sf::Uint16 x = ent->GetPosition().x;
    sf::Uint16 y = ent->GetPosition().y;

    SendPacket << x << y;
    Listener.Send(SendPacket, "127.0.0.1", 12345);
    SendPacket.Clear();
}

}
