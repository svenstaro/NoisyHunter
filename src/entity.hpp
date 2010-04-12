#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <boost/noncopyable.hpp>

#include <SFML/System.hpp>

// IEntity is an interface class for all game entities to use
class IEntity : boost::noncopyable {
public:
    // virtual 
    virtual ~IEntity() {}
    virtual sf::Drawable& GetDrawable() = 0;
    virtual void Update(float dt) = 0;
};
#endif
