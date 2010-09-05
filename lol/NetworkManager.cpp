#include "NetworkManager.hpp"

#include <boost/serialization/base_object.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <sstream>

namespace Engine {

NetworkManager::NetworkManager() {}
/*NetworkManager::NetworkManager(Root* root) {
    mRoot = root;
}*/
NetworkManager::~NetworkManager() {}

void NetworkManager::PreparePacket(){
}
void NetworkManager::AddEntity(Entity& entity){
    std::ostringstream os;
    boost::archive::binary_oarchive oa(os, boost::archive::no_header);
    //oa << entity;
//    mPacket << os.str();
}

void NetworkManager::SendPacket(){
}

void NetworkManager::HandleClients() {
}
}
