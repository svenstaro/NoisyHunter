#ifndef GUIGRID_HPP
#define GUIGRID_HPP

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_list.hpp>

#include "GuiControl.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiGrid : public GuiControl {
public:

	GuiGrid();

	GuiGrid(std::string name);

	~GuiGrid();

	GuiGrid* clone() const;

	void AddControl(GuiControl* guicontrol);

	void Draw(sf::RenderTarget* target, Vector2D offset = Vector2D(0,0));

    template < typename T >
    T* GetControl(const std::string& control_name) {
        BOOST_FOREACH(GuiControl& control, mChildren){
            if (control.GetName() == control_name){
                return (T*)&control;
            }
        }
        return NULL;
    }

private:
	boost::ptr_list<GuiControl> mChildren;
	TiledSprite mSprite;
};

}
#endif // GUIGRID_HPP
