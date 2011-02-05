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

	GuiGrid* create() const;

	void Draw(sf::RenderTarget* target);
	virtual void PlaceChildren();

	void SetColumns(int columns);
	int GetColumns() const;

private:
	int mColumns;
};

}
#endif // GUIGRID_HPP
