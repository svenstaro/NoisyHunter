#ifndef ROOTSERVER_HPP
#define ROOTSERVER_HPP

#include "Root.hpp"
#include "NetworkServer.hpp"


namespace Engine{

class RootServer : public Root{
public:
    void StartMainLoop();

    NetworkManager* GetNetworkManager();

private:
    NetworkServer mNetworkServer;
};

}

#endif
