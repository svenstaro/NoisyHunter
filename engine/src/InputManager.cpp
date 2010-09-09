#include "InputManager.hpp"
#include <iostream>
#include "Root.hpp"

namespace Engine{

InputManager::InputManager() {}
/*InputManager::InputManager(Root* root) {
    mRoot = root;
}*/
InputManager::~InputManager() {}


// TODO: Offset
const Coordinates InputManager::GetScreenCoordinates(const float world_x, const float world_y) const{
    Vector2D size = Root::get_const_instance().GetWindowSize();
    Coordinates c;
    c.X = world_x;
    c.Y = world_y;
    c.ScreenX = size.x * world_x;
    c.ScreenY = size.y * world_y;

    return c;
}
const Coordinates InputManager::GetWorldCoordinates(const int screen_x, const int screen_y) const {
    Vector2D size = Root::get_const_instance().GetWindowSize();
    Coordinates c;
    c.X = screen_x * 1.0 / size.x;  // make sure to get a float !!
    c.Y = screen_y * 1.0 / size.y;  // same here.
    c.ScreenX = screen_x;
    c.ScreenX = screen_x;
    return c;
}

void InputManager::BindKey(KeyBindingCallback callback, KeyboardEventType type, sf::Key::Code key) {
    mKeyBindings.push_back(new KeyBinding(callback, type, key));
}

void InputManager::BindMouse(MouseBindingCallback callback, MouseEventType type, sf::Mouse::Button button) {
    mMouseBindings.push_back(new MouseBinding(callback, type, button));
}


void InputManager::HandleEvent(sf::Event e) {
    // check for keyboard event
    if (e.Type == sf::Event::KeyPressed or
        e.Type == sf::Event::KeyReleased){

        for (boost::ptr_list<KeyBinding>::iterator i = mKeyBindings.begin(); i != mKeyBindings.end(); ++i) {
            if ( i->Key == e.Key.Code){

                if ((i->EventType == KEY_PRESSED and e.Type == sf::Event::KeyPressed ) or
                    (i->EventType == KEY_RELEASED and e.Type == sf::Event::KeyReleased ))
                        i->Callback();
            }
        }

    }

    // check for mouse event
    if (e.Type == sf::Event::MouseButtonPressed or
        e.Type == sf::Event::MouseButtonReleased or
        e.Type == sf::Event::MouseMoved or
        e.Type == sf::Event::MouseWheelMoved){

        for (boost::ptr_list<MouseBinding>::iterator i = mMouseBindings.begin(); i != mMouseBindings.end(); ++i) {
            if ((i->EventType == BUTTON_PRESSED and e.Type == sf::Event::MouseButtonPressed) and
                i->Button == e.MouseButton.Button){
                MouseEventArgs a;
                a.ScreenX = e.MouseButton.X;
                a.ScreenY = e.MouseButton.Y;
                Coordinates c = GetWorldCoordinates(a.ScreenX, a.ScreenY);
                a.X = c.X;
                a.Y = c.Y;
                i->Callback(a);
            }
            else if ((i->EventType == BUTTON_RELEASED and e.Type == sf::Event::MouseButtonReleased) and
                i->Button == e.MouseButton.Button){

                MouseEventArgs a;
                a.ScreenX = e.MouseButton.X;
                a.ScreenY = e.MouseButton.Y;
                Coordinates c = GetWorldCoordinates(a.ScreenX, a.ScreenY);
                a.X = c.X;
                a.Y = c.Y;
                i->Callback(a);
            }
            else if (i->EventType == MOUSE_MOVED and e.Type == sf::Event::MouseMoved){
                MouseEventArgs a;
                a.ScreenX = e.MouseButton.X;
                a.ScreenY = e.MouseButton.Y;
                Coordinates c = GetWorldCoordinates(a.ScreenX, a.ScreenY);
                a.X = c.X;
                a.Y = c.Y;
                i->Callback(a);
            }
            else if (i->EventType == WHEEL_MOVED and e.Type == sf::Event::MouseWheelMoved){
                MouseEventArgs a;
                a.WheelDelta = e.MouseWheel.Delta;
                i->Callback(a);
            }
        }

    }

}





}
