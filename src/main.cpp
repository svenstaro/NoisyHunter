#include <iostream>
#include <cstring>

#include "client.hpp"
#include "server.hpp"
#include "network.hpp"

int main(int argc, char* argv[]) {
    // TODO: use boost program options instead
    if(argc <= 1) {
        std::cerr << "ERROR: Pass either --client or --server" << std::endl;
        return EXIT_FAILURE;
    }
    else if(strcmp(argv[1], "--client") == 0) {
        ClientApp Client(800, 600, CLIENT_PORT);
        if(!Client.Init())
            return EXIT_FAILURE;
        Client.Run(); // will block and return when the user has quit the game
        Client.Cleanup();
    }
    else if(strcmp(argv[1], "--server") == 0) {
        ServerApp Server(SERVER_PORT);
        if(!Server.Init())
            return EXIT_FAILURE;
        Server.Run(); // will block and return when the server is shutdown
        Server.Cleanup();
    }
    
    return EXIT_SUCCESS;
}
