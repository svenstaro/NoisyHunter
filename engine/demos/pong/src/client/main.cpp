#include "Root.hpp"

#include "GameState.hpp"
#include "GameWorld.hpp"
#include "Ball.hpp"

int main() {
    Engine::Root& root = Engine::Root::get_mutable_instance();
    auto idmgr = root.GetIdManagerPtr();
    idmgr->RegisterEntityClass(new Ball());
    idmgr->RegisterWorldClass(new GameWorld());

    root.SetWorldPixelsPerFloat(500);
    root.InitializeAsClient(sf::VideoMode(600,600), "Pong Demo", false, sf::IpAddress("localhost"), 12356, "Player", true);

    GameState* s = new GameState();
    root.GetStateManagerPtr()->Add(s);

    root.StartMainLoop();

    return 0;
}
