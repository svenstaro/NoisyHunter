#include "Root.hpp"

#include "PlayState.hpp"

int main(){

    Engine::Root& root = Engine::Root::get_mutable_instance();
    root.InitializeAsClient(sf::VideoMode(800,600), "NoisyHunter", false, sf::IPAddress("localhost"), 12356);

    root.GetStateManagerPtr()->Add(new PlayState());

    root.StartMainLoop();
    return 0;
}

