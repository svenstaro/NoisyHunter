#ifndef GUICONTAINER_HPP
#define GUICONTAINER_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>

#include "GuiControl.hpp"

namespace Engine {

class GuiContainer : public GuiControl {
public:
	~GuiContainer();

	virtual GuiContainer* create() const = 0;

	bool AddControl(GuiControl* control);

	virtual void SetPosition(const float x, const float y);
	virtual void SetPosition(const Vector2D position);
	virtual void SetDimension(const Vector2D dimension);

	virtual void Update(float time_delta);
	virtual void PlaceChildren() = 0;
	virtual void Draw(sf::RenderTarget *target);

	// INTERNAL EVENT CALLBACKS FOR REDIRECTION TO CHILD ENTITIES
	virtual void OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
	virtual void OnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
	virtual void OnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y);
	virtual void OnKeyDown(const sf::Key::Code key);
	virtual void OnKeyUp(const sf::Key::Code key);
	virtual void OnType(const sf::Uint32 unicode_char);

	template < typename T >
	T* GetControl(const std::string& control_name) {
		BOOST_FOREACH(GuiControl& control, mControls){
			if (control.GetName() == control_name){
				return (T*)&control;
			}
		}
		return NULL;
	}

protected:
	boost::ptr_vector<GuiControl> mControls;
};

}

#endif
