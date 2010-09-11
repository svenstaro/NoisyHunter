#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "State.hpp"
#include "InputManager.hpp"

class LoadingState : public Engine::State{
public:
    LoadingState();
    ~LoadingState();

    // state control
    void Initialize();
    void Shutdown();
    //void Update(float time_delta);

    void OnCancel();
    void OnClick(Engine::MouseEventArgs args);
    void OnAnyKeyPressed();
private:

};

#endif
