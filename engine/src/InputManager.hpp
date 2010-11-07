#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/ptr_container/ptr_list.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <SFML/Graphics.hpp>

#include "Vector2D.hpp"
#include "Coordinates.hpp"

namespace Engine {

class MouseEventArgs : public Coordinates {
public:
	int WheelDelta;
};

// callback function typedefs
typedef boost::function<void()> KeyBindingCallback;
typedef boost::function<void(MouseEventArgs args)> MouseBindingCallback;

enum KeyboardEventType{
	KEY_PRESSED,
	KEY_RELEASED
};

enum MouseEventType{
	BUTTON_PRESSED,
	BUTTON_RELEASED,
	MOUSE_MOVED,
	WHEEL_MOVED
};

class KeyBinding {
public:
	KeyBinding(KeyBindingCallback callback, KeyboardEventType event_type) {
		// TODO: This stuff really shouldn't be implemented in the headers!
		Callback = callback;
		EventType = event_type;
		UseAnyKey = true;
	}

	KeyBinding(KeyBindingCallback callback, KeyboardEventType event_type,
			   sf::Key::Code key) {
		// TODO: This stuff really shouldn't be implemented in the headers!
		Callback = callback;
		Callback = callback;
		EventType = event_type;
		Key = key;
		UseAnyKey = false;
	}

	sf::Key::Code Key;
	KeyboardEventType EventType;
	KeyBindingCallback Callback;
	bool UseAnyKey;
};

class MouseBinding{
public:
	MouseBinding(MouseBindingCallback callback, MouseEventType event_type,
				 sf::Mouse::Button button = sf::Mouse::Left) {
		// TODO: This stuff really shouldn't be implemented in the headers!
		Callback = callback;
		Callback = callback;
		EventType = event_type;
		Button = button;
	}

	MouseBindingCallback Callback;
	MouseEventType EventType;
	sf::Mouse::Button Button;
};


class InputManager {
public:
	InputManager();
	//InputManager(Root* root);
	~InputManager();

	void HandleEvent(sf::Event e);

	void BindKey(KeyBindingCallback callback, KeyboardEventType type);
	void BindKey(KeyBindingCallback callback, KeyboardEventType type, sf::Key::Code key);
	void BindMouse(MouseBindingCallback callback, MouseEventType type,
			sf::Mouse::Button button = sf::Mouse::Left);

	Vector2D GetMousePosition() const;
	bool IsMouseButtonDown(sf::Mouse::Button button);

private:
	boost::ptr_list<KeyBinding> mKeyBindings;
	boost::ptr_list<MouseBinding> mMouseBindings;
};

}
#endif
