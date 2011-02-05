#ifndef SERVEREDITSTATE_HPP
#define SERVEREDITSTATE_HPP

#include <SFML/System/Vector2.hpp>

#include "Logger.hpp"
#include "State.hpp"
class ServerEditState : public Engine::State {
public:
	ServerEditState();
	~ServerEditState();

    // state control
    void Initialize();
    void Shutdown();

	void OnClientConnected(sf::Uint16 client_id);
};

#endif
