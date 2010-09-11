#include "LoadingState.hpp"

#include "Root.hpp"
#include "GuiControl.hpp"

LoadingState::LoadingState() {}
LoadingState::~LoadingState() {}

// state control
void LoadingState::Initialize() {
    // load gui resources


    // create gui
    CreateGuiSystem();

    Engine::GuiControl* c = new Engine::GuiControl("test");
    c->SetDimension(Engine::Vector2D(100,30));
    c->SetPosition(Engine::Vector2D(20,20));
    mGuiSystems.begin()->AddControl(c);

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
