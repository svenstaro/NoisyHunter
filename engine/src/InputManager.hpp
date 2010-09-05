#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/ptr_container/ptr_list.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <SFML/Graphics.hpp>

//#include "Root.hpp"

namespace Engine{



// Structure holding screen and game coordinates

struct Coordinates{
public:
    float X, Y;
    int ScreenX, ScreenY;
};


typedef boost::function<void()> KeyBindingCallback;

class KeyBinding{
public:
    KeyBinding(sf::Key::Code key, sf::Event::EventType event_type, KeyBindingCallback callback ) {
        Key = key;
        EventType = event_type;
        Callback = callback;
    }

    sf::Key::Code Key;
    sf::Event::EventType EventType;
    KeyBindingCallback Callback;
};

/*struct MouseBinding{
public:
    sf::Key::Code Button;
    sf::Event::Type EventType;
    void (*Callback)(const Coordinates);
}*/



class InputManager {
public:
    InputManager();
    //InputManager(Root* root);
    ~InputManager();

    void HandleEvent(sf::Event e);

    void BindKey(sf::Key::Code key, sf::Event::EventType type,  KeyBindingCallback callback );

private:
    //Root* mRoot;
    boost::ptr_list<KeyBinding> mKeyBindings;

};


}
#endif
