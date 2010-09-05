#include "InputManager.hpp"
#include <iostream>

namespace Engine{

InputManager::InputManager() {}
/*InputManager::InputManager(Root* root) {
    mRoot = root;
}*/
InputManager::~InputManager() {}

void InputManager::BindKey(sf::Key::Code key, sf::Event::EventType type,  KeyBindingCallback callback) {
    mKeyBindings.push_back(new KeyBinding(key, type, callback));
}


void InputManager::HandleEvent(sf::Event e) {
    if (e.Type == sf::Event::KeyPressed or e.Type == sf::Event::KeyReleased){
        for (boost::ptr_list<KeyBinding>::iterator i = mKeyBindings.begin(); i != mKeyBindings.end(); ++i) {
            if ( i->Key == e.Key.Code and i->EventType == e.Type){
                i->Callback();
            }
        }
    }
}


}
