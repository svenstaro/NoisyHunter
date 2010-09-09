#include "Root.hpp"

#include "PlayState.hpp"

int main(){

    Engine::Vector2D r(1,0);
    Engine::Vector2D u(-1,-0.01);
    std::cout << Engine::Vector2D::rad2Deg( Engine::Vector2D::Angle(r,u) ) << std::endl;

    std::cout << Engine::Vector2D::rad2Deg( u.Rotation() - r.Rotation() ) << std::endl;


    Engine::Root& root = Engine::Root::get_mutable_instance();
    root.InitializeAsClient(sf::VideoMode(800,600), "NoisyHunter", false, sf::IPAddress("localhost"), 12356);

    root.GetStateManagerPtr()->Add(new PlayState());

    root.StartMainLoop();
    return 0;
}

