#ifndef SERVERROOT_HPP
#define SERVERROOT_HPP

#include "Root.hpp"

namespace Engine{

class ServerRoot : public Root{
public:
    void StartMainLoop();

    const NetworkManager* GetNetworkManager() const;

private:
    NetworkServer mNetworkServer;
};

}

#endif
