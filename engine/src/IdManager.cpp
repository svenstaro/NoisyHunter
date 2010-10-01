#include <iostream>

#include "IdManager.hpp"

namespace Engine {

IdManager::IdManager() {}
IdManager::~IdManager() {}

void IdManager::RegisterEntityClass(Entity* default_object) {
    sf::Uint16 id = default_object->GetEntityId();

    if(mRegisteredEntityClasses.count(id) > 0) {
        // crash! you already have a class with that id registered...
        std::cerr << "## EXCEPTION ## IdManager::RegisterEntityClass ## Entity with UID " << id << " already registered." << std::endl;
        exit(1);
    }
    else {
        // insert into registered classes map (id >> default_object)
        mRegisteredEntityClasses[id] = default_object;
    }
}

Entity* IdManager::GetEntityPrototype(sf::Uint16 entity_id) {
    if(mRegisteredEntityClasses.count(entity_id) <= 0) {
        // there is no such prototype
        std::cerr << "## EXCEPTION ## IdManager::GetEntityPrototype ## Entity with UID " << entity_id << " not registered." << std::endl;
        exit(1);
    }
    Entity& copy = *mRegisteredEntityClasses[entity_id];
    return &copy;
}


}
