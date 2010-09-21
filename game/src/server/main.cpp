#include "Root.hpp"

#include "MainState.hpp"

int main(){
    Engine::Root& root = Engine::Root::get_mutable_instance();
    root.InitializeAsServer(12356);
    root.GetStateManagerPtr()->Add(new MainState());
    root.StartMainLoop();
    return 0;
}

