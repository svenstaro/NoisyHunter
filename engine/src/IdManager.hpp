#ifndef IDMANAGER_HPP
#define IDMANAGER_HPP

#include <SFML/System.hpp>

#include "Entity.hpp"
#include "World.hpp"

namespace Engine {

class IdManager {
public:
    IdManager();
    ~IdManager();

    void RegisterEntityClass(Entity* default_object);
    void RegisterWorldClass(World* default_object);

    Entity* GetEntityPrototype(sf::Uint16 entity_type_id);
    World* GetWorldPrototype(sf::Uint16 world_type_id);

	sf::Uint16 GetNewUniqueId();
	void ResetUniqueIds();

private:
	std::map<sf::Uint16, Entity* > mRegisteredEntityClasses;
	std::map<sf::Uint16, World* > mRegisteredWorldClasses;
	sf::Uint16 mNextUniqueId;
};

}

#endif
