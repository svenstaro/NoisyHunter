#include <boost/lexical_cast.hpp>

#include "IdManager.hpp"
#include "Root.hpp"

namespace Engine {

IdManager::IdManager() {
	ResetUniqueIds();
}
IdManager::~IdManager() {}

void IdManager::RegisterEntityClass(Entity* default_object) {
    sf::Uint16 id = default_object->GetEntityTypeId();

    if(mRegisteredEntityClasses.count(id) > 0) {
        // crash! you already have a class with that id registered...
		Logger::Critical(LogOrigin::IDMANAGER, "RegisterEntityClass ## Entity with TypeID " + boost::lexical_cast<std::string>(id) + " already registered.");
        exit(1);
    }
    else {
        // insert into registered classes map (id >> default_object)
        mRegisteredEntityClasses[id] = default_object;
    }
}

void IdManager::RegisterWorldClass(World* default_object) {
    sf::Uint16 id = default_object->GetWorldTypeId();

    if(mRegisteredWorldClasses.count(id) > 0) {
        // crash! you already have a class with that id registered...
		Engine::Logger::Critical(LogOrigin::IDMANAGER, "RegisterWorldClass ## World with TypeID " + boost::lexical_cast<std::string>(id) + " already registered.");
        exit(1);
    }
    else {
        // insert into registered classes map (id >> default_object)
        mRegisteredWorldClasses[id] = default_object;
    }
}

Entity* IdManager::GetEntityPrototype(sf::Uint16 entity_type_id) {
    if(mRegisteredEntityClasses.count(entity_type_id) <= 0) {
        // there is no such prototype
		Engine::Logger::Critical(LogOrigin::IDMANAGER, "GetEntityPrototype ## Entity with TypeID " + boost::lexical_cast<std::string>(entity_type_id) + " not registered.");
        exit(1);
    }
	return mRegisteredEntityClasses[entity_type_id]->create();
}

World* IdManager::GetWorldPrototype(sf::Uint16 world_type_id) {
    if(mRegisteredWorldClasses.count(world_type_id) <= 0) {
        // there is no such prototype
		Engine::Logger::Critical(LogOrigin::IDMANAGER, "GetWorldPrototype ## World with TypeID " + boost::lexical_cast<std::string>(world_type_id) + " not registered.");
        exit(1);
    }
    return mRegisteredWorldClasses[world_type_id]->clone();
}

sf::Uint16 IdManager::GetNewUniqueId() {
	mNextUniqueId++;
	return mNextUniqueId - 1;
}

void IdManager::ResetUniqueIds() {
	mNextUniqueId = 1000;
}

}
