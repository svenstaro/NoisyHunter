#include "StateManager.hpp"

#include "Root.hpp"

namespace Engine {

StateManager::StateManager() {}
/*StateManager::StateManager(Root* root){
    mRoot = root;
}*/
StateManager::~StateManager() {}

void StateManager::Shutdown() {
	// Shutdown all states
	while(mStates.size() > 0) {
		GetCurrentState().Shutdown();
		mStates.pop_back();
	}
}

void StateManager::BeginFrame() {

	for(int i = 0; i < mAmountToPop && mStates.size() > 0; i++) {
		GetCurrentState().Shutdown();
		mStates.pop_back();
		Root::get_mutable_instance().ResetView();
	}
	mAmountToPop = 0;

	while(!mStatesToAdd.empty()) {
		// Get new state from queue
		State* state = mStatesToAdd.front();
		mStatesToAdd.pop();

		// set arrow cursor as default when a new state is added
		Root::get_mutable_instance().GetResourceManagerPtr()->SetCursor(Engine::MOUSECURSOR_ARROW);
		state->Initialize();
		mStates.push_back(state);
		Root::get_mutable_instance().ResetView();
	}

	if(mStates.size() <= 0) {
		Root::get_mutable_instance().RequestShutdown();
	}
}

void StateManager::Update(float time_delta) {
	if(mStates.size() > 0) {
		// count back until you hit a state pausing the state below
		int i = mStates.size() - 1;
		while(i >= 0) {
			if(mStates[i].StatesBelowArePaused())
				break;
			else
				--i;
		}

		if(i < 0) 
			i = 0;

		// from this state on, update every state above
		while(i <= int(mStates.size()) - 1) {
			mStates[i].Update(time_delta);
			++i;
		}
	}
}

void StateManager::HandleEvent(sf::Event e) {
    if(mStates.size() > 0)
		GetCurrentState().HandleEvent(e);
}

void StateManager::Draw(sf::RenderTarget* target) {
	if(mStates.size() > 0) {
		// count back until you hit a state pausing the state below
		int i = mStates.size() - 1;
		while(i >= 0) {
			if(mStates[i].StatesBelowAreHidden())
				break;
			else
				--i;
		}

		if(i < 0) 
			i = 0;

		// from this state on, update every state above
		while(i <= int(mStates.size()) - 1) {
			mStates[i].Draw(target);
			++i;
		}
	}
}

void StateManager::Add(State* state) {
	mStatesToAdd.push(state);
}

void StateManager::Pop(int amount) {
	mAmountToPop += amount;
}

void StateManager::AppendAllEntitiesToPacket() {
    if(mStates.size() > 0)
		GetCurrentState().AppendAllEntitiesToPacket();
}

State& StateManager::GetCurrentState() {
	// TODO: will break when there is no state (in the future)
	return mStates.back();
}

bool StateManager::IsCurrentState(State* state) {
	return &GetCurrentState() == state;
}

void StateManager::SendWorldSnapshots() {
    if(mStates.size() > 0)
		GetCurrentState().SendWorldSnapshots();
}

}
