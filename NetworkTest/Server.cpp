#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "Server.hpp"
#include "ClientManager.hpp"

#include <iostream>
#include <string>

int main() {

	Engine::ClientManager ClMan(8);

	bool running = true;

	sf::SocketUDP Socket;
	sf::Packet Packet;

	sf::IPAddress Sender;
	sf::Uint16 Port;

	sf::Clock Clock;
	const float fps = 50.f;
	const float dt = 1/fps;
	float timebudget = 0.6f;
	sf::Clock LOLClock;

	if(!Socket.Bind(1337)) {
		std::cout << "fail port binding" << std::endl;
	}
	while(running) {
		
		float time_delta = Clock.GetElapsedTime();
		Clock.Reset();
		timebudget -= dt;

		while(time_delta < timebudget) {
			sf::Sleep(0.005);
			timebudget -= dt;
		}

		if(Socket.Receive(Packet, Sender, Port) == sf::Socket::Done) {
			if(!ClMan.IsKnown(Sender, Port)) {
				ClMan.Add(Sender, Port, "unnamed"); 
				std::cout << "Client added to ClMan" << boost::lexical_cast<std::string>(Port) << std::endl;
			} else {
				std::string cmd1;
				Packet >> cmd1;
				std::cout << cmd1 << std::endl;
				if(cmd1 == "Hello") {
					std::string name;
					Packet >> name;
					sf::Uint16 id = ClMan.GetId(Sender, Port);
					ClMan.SetName(id, name);
					std::cout << "CLient connected ["+boost::lexical_cast<std::string>(id)+" | "+name+"]" << std::endl;
					Packet.Clear();
					Packet << "kthx";
					Socket.Send(Packet, Sender, Port);
				} else if(cmd1 == "Ping") {
					std::cout << "Got ping from Client ["+boost::lexical_cast<std::string>(ClMan.GetId(Sender,Port))+" | "+ClMan.GetName(ClMan.GetId(Sender,Port))+"]" << std::endl;
				} else if(cmd1 == "Bye") {
					ClMan.Remove(ClMan.GetId(Sender,Port));
				}
			}
		}

		if (LOLClock.GetElapsedTime() >= 0.2f) {
			LOLClock.Reset();
			Packet.Clear();


			BOOST_FOREACH(sf::Uint16 id, ClMan.GetIds()) {
				Packet.Clear();
				Packet << sf::Uint16(ClMan.GetActiveClients());
				BOOST_FOREACH(sf::Uint16 id2, ClMan.GetIds()) {
					Packet << ClMan.GetName(id2);
				}
				Socket.Send(Packet, ClMan.GetIp(id), ClMan.GetPort(id));
			}
		}
	}
}
