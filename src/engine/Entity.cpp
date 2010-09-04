#include "Entity.hpp"

namespace Engine {

	Entity::operator < (const Entity& other){
		return mLayer < other.GetLayer();
	}


}
