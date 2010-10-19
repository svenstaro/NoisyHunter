#include <boost/lexical_cast.hpp>
#include <SFML/Network.hpp>

#include "ClientManager.hpp"

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

    std::map<sf::Uint16, Client>::iterator it2;
	bool id_found = false;
	for(it2 = mClients.begin(); it2 != mClients.end(); it2++) {
        if(it2->second.name == name) {
			id_found = true;
            break;
        }
    }
	if(id_found) {
		sf::Uint16 rnd = sf::Randomizer::Random(100,999);
		client.name = name + boost::lexical_cast<std::string>(rnd);
	} else {
	    client.name = name;
	}
    mClients.insert(std::pair<sf::Uint16, Client>(it->first, client));
}

void ClientManager::Remove(const sf::Uint16 id) {
    mClients.erase(id);
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
	if(mClients.size() == 0) {
		exit(1);
	}

	std::vector<sf::Uint16> ids;
    std::map<sf::Uint16, Client>::iterator it;
    sf::Uint16 tmp = 0;
	for(it = mClients.begin(); it != mClients.end(); it++) {
		tmp = it->first;
        ids.push_back(tmp);
    }
    return ids;
}

sf::Uint16 ClientManager::GetId(const sf::IPAddress& address, const sf::Uint16 port) {
    std::map<sf::Uint16, Client>::iterator it;
	sf::Uint16 tmp = 0;
	bool id_found = false;
	for(it = mClients.begin(); it != mClients.end(); it++) {
        if(it->second.address == address && it->second.port == port) {
            tmp = it->first;
			id_found = true;
            break;
		}
    }
	if(!id_found) {
		exit(1);
	}
    return tmp;
}

sf::Uint16 ClientManager::GetId(const std::string& name) {
    std::map<sf::Uint16, Client>::iterator it;
    sf::Uint16 tmp = 0;
	bool id_found = false;
	for(it = mClients.begin(); it != mClients.end(); it++) {
        if(it->second.name == name) {
            tmp = it->first;
			id_found = true;
            break;
        }
    }
	if(!id_found) {
		exit(1);
	}
    return tmp;
}

sf::IPAddress ClientManager::GetIp(const sf::Uint16 id) {
	if(mClients.count(id) >= 1) {
		return mClients[id].address;
	} else {
		exit(1);
	}

}

sf::Uint16 ClientManager::GetPort(const sf::Uint16 id) {
	if(mClients.count(id) >= 1) {
		return mClients[id].port;
	} else {
		exit(1);
	}
}

std::string ClientManager::GetName(const sf::Uint16 id) {
	if(mClients.count(id) >= 1) {
		return mClients[id].name;
	} else {
		exit(1);
	}
}

sf::Uint16 ClientManager::GetMaxPlayers() {
    return mMaxPlayers;
}

sf::Uint16 ClientManager::GetActiveClients() {
    return mClients.size();
}

void ClientManager::SetName(const sf::Uint16 id, const std::string& new_name) {
	if(mClients.count(id) >= 1) {
		mClients[id].name = new_name;
	} else {
		exit(1);
	}
}

void ClientManager::SetMaxPlayers(const sf::Uint16 new_max_players) {
	mMaxPlayers = new_max_players;
}

}
