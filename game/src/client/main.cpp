#include "Root.hpp"

#include "PlayState.hpp"
#include "LoadingState.hpp"

int main(){
    Engine::Root& root = Engine::Root::get_mutable_instance();
    root.InitializeAsClient(sf::VideoMode(800,600), "NoisyHunter", false, sf::IPAddress("localhost"), 12356, "Rolf-Peter");

    //root.GetStateManagerPtr()->Add(new LoadingState());
    root.GetStateManagerPtr()->Add(new PlayState());

    root.StartMainLoop();
    return 0;
}

