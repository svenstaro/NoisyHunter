
#include "Entity.hpp"

#include <boost/serialization/base_object.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sstream>
int main() {
    std::ostringstream os;
    boost::archive::binary_oarchive oa(os, boost::archive::no_header);
    //Torpedo t;
    //Engine::
    Entity e;
    oa << e;
    return 0;
}
