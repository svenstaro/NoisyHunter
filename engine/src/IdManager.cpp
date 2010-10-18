#include <boost/lexical_cast.hpp>

#include "IdManager.hpp"
#include "Root.hpp"

namespace Engine {

IdManager::IdManager() {
	ResetUniqueIds();
}
IdManager::~IdManager() {}

void IdManager::RegisterEntityClass(Entity* default_object) {
    sf::Uint16 id = default_object->GetEntityId();

    if(mRegisteredEntityClasses.count(id) > 0) {
        // crash! you already have a class with that id registered...
		Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_ERROR, LOGORIGIN_IDMANAGER, "RegisterEntityClass ## Entity with UID " + boost::lexical_cast<std::string>(id) + " already registered.");
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
        Root::get_mutable_instance().GetLogManagerPtr()->Log(LOGLEVEL_ERROR, LOGORIGIN_IDMANAGER, "GetEntityPrototype ## Entity with UID " + boost::lexical_cast<std::string>(entity_id) + " not registered.");
        exit(1);
    }
    Entity& copy = *mRegisteredEntityClasses[entity_id];
    return &copy;
}

sf::Uint16 IdManager::GetNewUniqueId() {
	mNextUniqueId++;
	return mNextUniqueId - 1;
}

void IdManager::ResetUniqueIds() {
	mNextUniqueId = 1000;
}

}
