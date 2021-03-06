#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include <SFML/System/Vector2.hpp>

#include "Logger.hpp"
#include "State.hpp"
#include "Submarine.hpp"
#include "Math.hpp"

class MainState : public Engine::State {
public:
    MainState();
    ~MainState();

    // state control
    void Initialize();
    void Shutdown();

	void OnClientConnected(sf::Uint16 client_id);
private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
