#include <iostream>

#include <SFML/Network.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[]){

    if (argc != 4){
        std::cout << "Usage: ./client SERVER_IP SERVER_PORT CLIENT_NAME" << std::endl;
        exit(1);
    }
    
    sf::SocketUDP mSocket;
    mSocket.Bind(23456);
    sf::IPAddress ip(argv[1]);
    sf::Uint16 port = boost::lexical_cast<sf::Uint16>(argv[2]);
    sf::Packet packet;
    std::string t = "Hello";
    std::string name = argv[3];
    packet << t << name;
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

        sf::IPAddress sip;
        sf::Uint16 sport;
        mSocket.Receive(packet, sip, sport);
        sf::Uint16 client_num;
        packet >> client_num;
        std::string lol = " Clients: ";
        for (int i = 0; i < client_num; i++){
            std::string client_name;
            packet >> client_name;
            lol += client_name;
        }
        std::cout << client_num << lol << std::endl;
        sf::Sleep(0.5);        
    }
    return 1;
}