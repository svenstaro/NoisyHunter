#ifndef GUIGRID_HPP
#define GUIGRID_HPP

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_list.hpp>

#include "GuiControl.hpp"
#include "GuiContainer.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiGrid : public GuiContainer {
public:

	GuiGrid();

	GuiGrid(std::string name);

	~GuiGrid();

	GuiGrid* clone() const;

	void Draw(sf::RenderTarget* target, Vector2D offset = Vector2D(0,0));

private:
	TiledSprite mSprite;
};

}
#endif // GUIGRID_HPP
