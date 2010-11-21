#ifndef IDMANAGER_HPP
#define IDMANAGER_HPP

#include <SFML/System.hpp>

#include "Entity.hpp"

namespace Engine {

class IdManager {
public:
    IdManager();
    ~IdManager();

    void RegisterEntityClass(Entity* default_object);

    Entity* GetEntityPrototype(sf::Uint16 entity_type_id);

	sf::Uint16 GetNewUniqueId();
	void ResetUniqueIds();

private:
	std::map<sf::Uint16, Entity* > mRegisteredEntityClasses;
	sf::Uint16 mNextUniqueId;
};

}

#endif
