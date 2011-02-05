#include "ServerEditState.hpp"
#include "Root.hpp"

ServerEditState::ServerEditState() {
}

ServerEditState::~ServerEditState() {
}

void ServerEditState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing ServerEditState.");
    
    // Bind connection events
    auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->BindOnClientConnected(boost::bind(&ServerEditState::OnClientConnected, this, _1));
	netmgr->SetEntityState(this);

	mAmountToPop = 0;

}

void ServerEditState::Shutdown() {
	Engine::Logger::Debug(Engine::LogOrigin::STATE, "Shutting down ServerEditState.");
}

void ServerEditState::OnClientConnected(sf::Uint16 client_id) {

}
