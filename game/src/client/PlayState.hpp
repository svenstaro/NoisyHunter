#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <string>

#include "LogManager.hpp"
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
    
    // network callbacks
    void OnClientConnected(const std::string& client_name);

private:
    Crosshair* mCrosshair;
};

#endif
