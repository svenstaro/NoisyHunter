#ifndef GUICONTAINER_HPP
#define GUICONTAINER_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>

#include "GuiControl.hpp"

namespace Engine {

class GuiContainer : public GuiControl {
public:
	~GuiContainer() = 0;

	virtual GuiContainer* clone() const;

	bool AddControl(GuiControl* control);

	void Draw(sf::RenderTarget *target, Vector2D offset = Vector2D(0,0));

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
