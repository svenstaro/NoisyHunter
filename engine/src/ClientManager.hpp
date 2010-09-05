#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <SFML/Network.hpp>

#include <string>
#include <map>

struct Client {
    sf::IPAddress address;
    std::string name;
    sf::Uint16 port;
};

class ClientManager {
    public:
        ClientManager(const sf::Uint16 max_players=4);

        ~ClientManager();

        void Add(const sf::IPAddress address, const sf::Uint16 port, const std::string name);

        void Remove(const sf::Uint16 id);

        bool IsKnown(const sf::IPAddress address);

        bool IsSlotAvailable();

        // Returns vector of currently active (connected) client IDs
        std::vector<sf::Uint16> GetIDs();

        sf::Uint16 GetID(const sf::IPAddress address);

        // Get IP of client ID
        sf::IPAddress GetIP(const sf::Uint16 id);

        sf::Uint16 GetPort(const sf::Uint16 id);
    
        // Get name of client ID
        std::string GetName(const sf::Uint16 id);

        sf::Uint16 GetMaxPlayers();

        sf::Uint16 GetActiveClients();

        // Set name of client ID
        void SetName(const sf::Uint16 id, const std::string name);

        void SetMaxPlayers(const sf::Uint16 max_players);

    private:
        sf::Uint16 m_max_players;
        std::map<sf::Uint16, Client> m_clients;
};

#endif
