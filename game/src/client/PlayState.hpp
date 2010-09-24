#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include "InputManager.hpp"
#include "Crosshair.hpp"
#include "Submarine.hpp"

class PlayState : public Engine::State {
public:
    PlayState();
    ~PlayState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);

    // input callbacks
    void OnSetNoisyMode();
    void OnSetSilentMode();

    void OnNavigateTo(const Engine::Coordinates& mouse_position);
    void OnFireTorpedo(const Engine::Coordinates& mouse_position);

    void OnLeaveGame();
    void OnClick(Engine::MouseEventArgs args);
    void OnRightClick(Engine::MouseEventArgs args);
    void OnMouseMove(Engine::MouseEventArgs args);
private:
    Submarine* mPlayerSubmarine;
    Crosshair* mCrosshair;
};

#endif
