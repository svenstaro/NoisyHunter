#include <SFML/Network.hpp>
#include "ClientManager.hpp"
#include "Root.hpp"

#include <string>
#include <map>


namespace Engine {
ClientManager::ClientManager(sf::Uint16 max_players) {
    mMaxPlayers = max_players;
}

ClientManager::~ClientManager() {}

void ClientManager::Add(const sf::IPAddress& address, const sf::Uint16 port, const std::string& name) {
    std::map<sf::Uint16, Client>::iterator it;
    it = mClients.end();
    Client client;
    client.address = address;
    client.port = port;
    client.name = name;
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_URGENT, LOGORIGIN_NETWORK, "Adding client "+name+" ("+address.ToString()+":"+boost::lexical_cast<std::string>(port)+").");
    mClients.insert(std::pair<sf::Uint16, Client>(it->first, client));
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Clients online now: "+boost::lexical_cast<std::string>(mClients.size()));
}

void ClientManager::Remove(const sf::Uint16 id) {
    mClients.erase(id);
	auto logmgr = Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(LOGLEVEL_VERBOSE, LOGORIGIN_NETWORK, "Clients online now: "+boost::lexical_cast<std::string>(mClients.size()));
}

bool ClientManager::IsKnown(const sf::IPAddress& address) {
    bool isknown = false;
    std::map<sf::Uint16, Client>::iterator it;
    for(it = mClients.begin(); it != mClients.end(); ++it) {
		if(it->second.address == address) {
			isknown = true;
			break;
        }
    }
    return isknown;
}

bool ClientManager::IsSlotAvailable() {
    if(mClients.size() >= mMaxPlayers) {
        return false;
    } else {
        return true;
    }
}

std::vector<sf::Uint16> ClientManager::GetIds() {
    std::vector<sf::Uint16> ids;
    std::map<sf::Uint16, Client>::iterator it;
    sf::Uint16 tmp = 0;
    for(it = mClients.begin() ; it != mClients.end(); it++) {
        tmp = (*it).first;
        ids.push_back(tmp);
    }
    return ids;
}

sf::Uint16 ClientManager::GetId(const sf::IPAddress& address) {
    std::map<sf::Uint16, Client>::iterator it;
    sf::Uint16 tmp = 0;
    for(it = mClients.begin() ; it != mClients.end(); it++) {
        if(it->second.address == address) {
            tmp = it->first;
            break;
        }
    }
    return tmp;
}

sf::Uint16 ClientManager::GetId(const std::string& name) {
    std::map<sf::Uint16, Client>::iterator it;
    sf::Uint16 tmp = 0;
    for(it = mClients.begin() ; it != mClients.end(); it++) {
        if(it->second.name == name) {
            tmp = it->first;
            break;
        }
    }
    return tmp;
}

sf::IPAddress ClientManager::GetIp(const sf::Uint16 id) {
	return mClients[id].address;
}

sf::Uint16 ClientManager::GetPort(const sf::Uint16 id) {
    return mClients[id].port;
}

std::string ClientManager::GetName(const sf::Uint16 id) {
    return mClients[id].name;
}

sf::Uint16 ClientManager::GetMaxPlayers() {
    return mMaxPlayers;
}

sf::Uint16 ClientManager::GetActiveClients() {
    return mClients.size();
}

void ClientManager::SetName(const sf::Uint16 id, const std::string& name) {
    mClients[id].name = name;
}

void ClientManager::SetMaxPlayers(const sf::Uint16 max_players) {
    mMaxPlayers = max_players;
}

}
