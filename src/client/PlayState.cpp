#include "PlayState.hpp"


PlayState::PlayState(Engine::Root* root){
    mRoot = root;
}
void PlayState::Initialize(){
    // create GUI

    // create entities
}
void PlayState::Shutdown(){
    // hm, what do we need shutdown for!?
}
void PlayState::OnSetNoisyMode(){
    mPlayerSubmarine.SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode(){
    mPlayerSubmarine.SetMode(Submarine::MODE_SILENT);
}
void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    mPlayerSubmarine.SetTarget(target);
}
void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    const Torpedo& torpedo = mPlayerSubmarine.FireTorpedoTo(target);

    AddEntity(torpedo);



}
