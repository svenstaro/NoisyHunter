#include <iostream>

#include <SFML/Network.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[]){

    if (argc != 4){
        std::cout << "Usage: ./client SERVER_IP SERVER_PORT CLIENT_NAME" << std::endl;
        exit(1);
    }
    
    sf::SocketUDP mSocket;
    sf::IPAddress ip(argv[1]);
    sf::Uint16 port = boost::lexical_cast<sf::Uint16>(argv[2]);
    sf::Packet packet;
    std::string t = "Hello";
    std::string name = argv[3];
    packet << t << name;
    mSocket.Send(packet, ip, port);
    mSocket.Send(packet, ip, port);
    std::cout << "Hello server, I am " << name << std::endl;

    int i = 0;
    while(1) {
        i++;
        std::cout << "Loop #" << i << std::endl;

        t = "Ping";
        packet.Clear();
        packet << t;

        mSocket.Send(packet, ip, port);
        sf::Sleep(0.5);        
    }
    return 1;
}
