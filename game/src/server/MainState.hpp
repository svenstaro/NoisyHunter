#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include "Submarine.hpp"

class MainState : public Engine::State{
public:
    MainState();
    ~MainState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);
	void OnClientConnect(sf::Uint16 cl_id);
};

#endif
