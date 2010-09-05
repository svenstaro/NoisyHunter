#include "StateManager.hpp"

namespace Engine{


StateManager::StateManager() {}
/*StateManager::StateManager(Root* root){
    mRoot = root;
}*/
StateManager::~StateManager() {}

void StateManager::Update(float time_delta){

}
void StateManager::Add(State* state){
    mStates.push_back(state);
}
void StateManager::Pop(int amount){

}



}
