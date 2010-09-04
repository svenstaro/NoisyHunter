#include "PlayState.hpp"

PlayState::PlayState() {}
PlayState::PlayState(Engine::Root* root){
    mRoot = root;
}
PlayState::~PlayState() {}

void PlayState::Initialize(){
    // create GUI

    // create entities

    // bind keys
}
void PlayState::Shutdown(){
    // hm, what do we need shutdown for!?
}
void PlayState::OnSetNoisyMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode(){
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}
void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position){
    //const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    //mPlayerSubmarine->SetTarget(target);
}
void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position){
    const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);

    AddEntity(torpedo);
}
