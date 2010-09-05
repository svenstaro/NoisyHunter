#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <fstream>
#include <boost/serialization/base_object.hpp>

//#include "Vector2D.hpp"

//namespace Engine {

class Entity {
    friend class boost::serialization::access;
public:
	Entity(){}
	~Entity(){}
   
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);

};

//}

#endif
