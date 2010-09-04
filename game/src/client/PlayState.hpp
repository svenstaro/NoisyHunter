#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include "Input.hpp"
#include "Submarine.hpp"

class PlayState : Engine::State{
public:
    PlayState(Engine::Root* root);
    ~PlayState();

    // state control
    void Initialize();
    void Shutdown();

    // input callbacks
    void OnSetNoisyMode();
    void OnSetSilentMode();

    void OnNavigateTo(const Engine::Coordinates& mouse_position);
    void OnFireTorpedo(const Engine::Coordinates& mouse_position);

private:
    PlayState() {}

    Submarine* mPlayerSubmarine;
};

#endif
