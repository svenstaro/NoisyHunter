#include "Root.hpp"

int main(){
    Engine::Root& root = Engine::Root::get_mutable_instance();
    root.InitializeAsServer(12356);
    root.StartMainLoop();
    return 0;
}

