#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

//#include "Root.hpp"
#include "State.hpp"

namespace Engine {

class StateManager {
public:
    StateManager();
    //StateManager(Root* root);
    ~StateManager();

	void Shutdown();

    void Update(float time_delta);
    void HandleEvent(sf::Event e);
    void Draw(sf::RenderTarget* target);
    void Add(State* state);
    void Pop(int amount = 1);
    void AppendAllEntitiesToPacket();
	State& GetCurrentState();
	bool IsCurrentState(State* state);
	void SendWorldSnapshots();

private:
    //Root* mRoot;
    boost::ptr_vector<State> mStates;
	int mAmountToPop;
};

}
#endif
