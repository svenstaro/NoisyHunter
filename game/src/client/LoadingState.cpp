#include "LoadingState.hpp"

#include "Root.hpp"

LoadingState::LoadingState() {}
LoadingState::~LoadingState() {}

// state control
void LoadingState::Initialize() {
    // load gui resources

    // create gui

    // (create entities)

    // bind input events
}
void LoadingState::Shutdown() {}
//void Update(float time_delta);

void LoadingState::OnCancel() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
void LoadingState::OnClick(Engine::MouseEventArgs args) {
    // load playstate if finished loading
}
void LoadingState::OnAnyKeyPressed() {
    // load playstate if finished loading
}
