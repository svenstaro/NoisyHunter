#include "Root.hpp"
#include "MainState.hpp"
#include "GameWorld.hpp"

int main() {
    Engine::Root& root = Engine::Root::get_mutable_instance();

    auto idmgr = root.GetIdManagerPtr();
    idmgr->RegisterEntityClass(new Ball());
    idmgr->RegisterWorldClass(new GameWorld());

    root.SetWorldPixelsPerFloat(500);
    root.InitializeAsServer(12356, true);
    
    MainState* mainstate = new MainState();

    GameWorld* gameworld = new GameWorld();
    gameworld->InitializePhysics();
    gameworld->GrabWorldUniqueId();
    mainstate->AddWorld(gameworld);

	root.GetStateManagerPtr()->Add(mainstate);
    root.StartMainLoop();

    return 0;
}
