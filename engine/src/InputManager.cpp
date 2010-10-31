#include "InputManager.hpp"
#include <iostream>
#include "Root.hpp"

namespace Engine {

InputManager::InputManager() {}
InputManager::~InputManager() {}

Vector2D InputManager::GetMousePosition() const {
    return Root::get_mutable_instance().GetMousePosition();
}

void InputManager::BindKey(KeyBindingCallback callback, KeyboardEventType type, sf::Key::Code key) {
    mKeyBindings.push_back(new KeyBinding(callback, type, key));
}

void InputManager::BindKey(KeyBindingCallback callback, KeyboardEventType type) {
    mKeyBindings.push_back(new KeyBinding(callback, type));
}

void InputManager::BindMouse(MouseBindingCallback callback, MouseEventType type, sf::Mouse::Button button) {
    mMouseBindings.push_back(new MouseBinding(callback, type, button));
}

void InputManager::HandleEvent(sf::Event e) {
    // check for keyboard event
	if(e.Type == sf::Event::KeyPressed or e.Type == sf::Event::KeyReleased) {
		for(auto i = mKeyBindings.begin(); i != mKeyBindings.end(); ++i) {
			if(i->Key == e.Key.Code or i->UseAnyKey) {
				if((i->EventType == KEY_PRESSED and e.Type == sf::Event::KeyPressed) or
						(i->EventType == KEY_RELEASED and e.Type == sf::Event::KeyReleased))
					i->Callback();
			}
		}
	}

    // check for mouse event
    if(e.Type == sf::Event::MouseButtonPressed or
			e.Type == sf::Event::MouseButtonReleased or
			e.Type == sf::Event::MouseMoved or
			e.Type == sf::Event::MouseWheelMoved) {

        for(auto i = mMouseBindings.begin(); i != mMouseBindings.end(); ++i) {
            if((i->EventType == BUTTON_PRESSED and
					e.Type == sf::Event::MouseButtonPressed)
					and i->Button == e.MouseButton.Button) {
                MouseEventArgs a;
				a.SetScreenPixel(Vector2D(e.MouseButton.X, e.MouseButton.Y));
                i->Callback(a);
            } else if((i->EventType == BUTTON_RELEASED and
					e.Type == sf::Event::MouseButtonReleased) and 
					i->Button == e.MouseButton.Button) {
                MouseEventArgs a;
				a.SetScreenPixel(Vector2D(e.MouseButton.X, e.MouseButton.Y));
                i->Callback(a);
			} else if(i->EventType == MOUSE_MOVED and
					e.Type == sf::Event::MouseMoved) {
                MouseEventArgs a;
				a.SetScreenPixel(Vector2D(e.MouseMove.X, e.MouseMove.Y));
                i->Callback(a);
            } else if(i->EventType == WHEEL_MOVED and
					e.Type == sf::Event::MouseWheelMoved) {
                MouseEventArgs a;
                a.WheelDelta = e.MouseWheel.Delta;
				i->Callback(a);
            }
        }
    }
}

}
