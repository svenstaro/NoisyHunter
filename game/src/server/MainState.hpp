#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "LogManager.hpp"
#include "State.hpp"
#include "Submarine.hpp"

class MainState : public Engine::State{
public:
    MainState();
    ~MainState();

    // state control
    void Initialize();
    void Shutdown();

    void Update(float time_delta);
	void OnClientConnected(std::string client_name);
private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
