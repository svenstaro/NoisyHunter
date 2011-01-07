#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"

class GameState : public Engine::State {
public:
    GameState();
    ~GameState();

    void Initialize();
    void Shutdown();

    void Update(float time_delta);

    // callbacks here 
    void OnPressUp();
    void OnPressDown();
	void OnPressEscape();
};

#endif
