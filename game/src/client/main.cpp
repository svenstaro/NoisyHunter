#include "ClientRoot.hpp"

int main(){

    Engine::ClientRoot root;
    root.Initialize(sf::VideoMode(800,600), "NoisyHunter");

    root.StartMainLoop();
    return 0;
}

