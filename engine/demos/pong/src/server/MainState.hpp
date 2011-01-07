#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "State.hpp"
#include "Ball.hpp"

class MainState : public Engine::State {
public:
    MainState();
    ~MainState();

    void Initialize();
    void Shutdown();
};

#endif
