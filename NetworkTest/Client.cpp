#include <iostream>

#include <SFML/Network.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[]){

    if (argc != 5){
        std::cout << "Usage: ./Client.bin SERVER_IP SERVER_PORT CLIENT_NAME CLIENT_PORT" << std::endl;
        exit(1);
    }
	sf::Uint16 cl_port = boost::lexical_cast<sf::Uint16>(argv[4]);

    sf::SocketUDP mSocket;
    if(!mSocket.Bind(cl_port)) {
		std::cout << "Cannot bind to port " << argv[4] << std::endl;
	    if(!mSocket.Bind(23457)) {
			std::cout << "Cannot bind to port 23457" << std::endl;
			if(!mSocket.Bind(23458)) {
				std::cout << "Cannot bind to port 23458" << std::endl;
				if(!mSocket.Bind(23459)) {
					std::cout << "Cannot bind to port 23459; verkackt" << std::endl;
				}
			}
		}
	}
	mSocket.SetBlocking(0);
    sf::IPAddress ip(argv[1]);
    sf::Uint16 port = boost::lexical_cast<sf::Uint16>(argv[2]);
    sf::Packet packet;
    std::string t = "Hello";
    std::string name = argv[3];
	sf::IPAddress sip;
	sf::Uint16 sport;
	bool connected = false;
	while (!connected) {
		packet << t << name;
	    mSocket.Send(packet, ip, port);
	    std::cout << "Hello server, I am " << name << std::endl;
		packet.Clear();
		if (mSocket.Receive(packet, sip, sport) == sf::Socket::Done) {
			std::string tmp;
			packet >> tmp;
			if(tmp=="kthx")
				connected=true;
		}
		sf::Sleep(0.4);
	}

    int i = 0;
    while(1) {
        i++;
        std::cout << "Loop #" << i << std::endl;

        t = "Ping";
        packet.Clear();
        packet << t;

        mSocket.Send(packet, ip, port);

        mSocket.Receive(packet, sip, sport);
        sf::Uint16 client_num;
        packet >> client_num;
        std::string lol = " Clients: ";
        for (int i = 0; i < client_num; i++){
            std::string client_name;
            packet >> client_name;
            lol += client_name+" | ";
        }
        std::cout << client_num << lol << std::endl;
        sf::Sleep(0.2);        
    }
    return 1;
}
