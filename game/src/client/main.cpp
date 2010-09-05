#include "RootClient.hpp"

int main(){

    Engine::RootClient root;
    root.Initialize(sf::VideoMode(800,600), "NoisyHunter");

    root.StartMainLoop();
    return 0;
}

