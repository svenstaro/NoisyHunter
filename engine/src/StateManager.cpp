#include "StateManager.hpp"

namespace Engine{


StateManager::StateManager() {}
/*StateManager::StateManager(Root* root){
    mRoot = root;
}*/
StateManager::~StateManager() {}

void StateManager::Update(float time_delta){
    if (mStates.size() > 0)
        mStates.back().Update(time_delta);
}
void StateManager::Draw(sf::RenderTarget* target){
    if (mStates.size() > 0)
        mStates.back().Draw(target);
}
void StateManager::Add(State* state){
    mStates.push_back(state);
    state->Initialize();
}
void StateManager::Pop(int amount){

}



}
