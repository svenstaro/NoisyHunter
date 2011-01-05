#include "GuiGrid.hpp"

#include "Root.hpp"

namespace Engine{

GuiGrid::GuiGrid() {}
GuiGrid::GuiGrid(std::string name) {
	mName = name;

	SetPositionType(POSITIONTYPE_SCREENPIXEL);
}
GuiGrid::~GuiGrid() {}

GuiGrid* GuiGrid::create() const {
	return new GuiGrid();
}

void GuiGrid::Draw(sf::RenderTarget* target) {
	// Draw children
	BOOST_FOREACH(GuiControl& gc, mControls) {
		gc.Draw(target);
	}

	DrawAllAttachments(target);
}

void GuiGrid::PlaceChildren() {
	int i = 0;
	BOOST_FOREACH(GuiControl& gc, mControls) {
		gc.SetPosition(Engine::Vector2D(mPosition.x + 0, mPosition.y + i*1.f/mControls.size()*mDimension.y));
		gc.SetDimension(Engine::Vector2D(mDimension.x, 1.f/mControls.size()*mDimension.y));
		++i;
	}
}

}
