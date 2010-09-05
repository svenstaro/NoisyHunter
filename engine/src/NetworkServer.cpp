#include "NetworkServer.hpp"

namespace Engine {

void NetworkServer::Initialize(const sf::Uint16 port) {
    if (!Listener.Bind(port)) {
        std::cerr << "Your penis was broken by the NetworkManager while binding the listening socket" << std::endl;
        exit(1);
    }

    mSelector.Add(Listener);
}

void NetworkServer::HandleClients() {
    unsigned int nb_sockets = mSelector.Wait();

    for (unsigned int i=0;i < nb_sockets; ++i) {
        sf::SocketUDP socket = mSelector.GetSocketReady(i);

        if (socket == Listener) {
            sf::IPAddress address;
            sf::SocketUDP client;
            std::cout << "[NETWORK] Your penis shots out a client from [" << address << "]." << std::endl;

            mSelector.Add(client);
        } else { // Handle a connected client
            sf::Packet packet;
            sf::IPAddress client_address;
            sf::Uint16 client_port;

            if (socket.Receive(packet, client_address, client_port) == sf::Socket::Done) {
                sf::Uint16 x;
                sf::Uint16 y;
                packet >> x >> y;
                std::cout << "Your penis looks quite interested at you and says :\"" << x << y << "\"" << std::endl;
                packet.Clear();
                // TODO: Handle client later here
            } else {
                mSelector.Remove(socket);
            }
        }
    }
}
}
