#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include <SFML/System/Vector2.hpp>

#include "LogManager.hpp"
#include "State.hpp"
#include "Submarine.hpp"

class MainState : public Engine::State {
public:
    MainState();
    ~MainState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);
	void OnClientConnected(sf::Uint16 client_id, sf::Uint16 world_unique_id);
private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
