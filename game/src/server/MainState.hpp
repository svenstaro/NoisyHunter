#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP

#include "LogManager.hpp"
#include "State.hpp"
#include "Submarine.hpp"
#include "Interaction.hpp"

class MainState : public Engine::State{
public:
    MainState();
    ~MainState();

    // state control
    void Initialize();
    void Shutdown();

	void HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data);

    void Update(float time_delta);
	void OnClientConnected(std::string client_name);
private:
	// TEEEEEEST TEST
	bool mTargetSet;
};

#endif
