#include "GuiGrid.hpp"

#include "Root.hpp"

namespace Engine{

GuiGrid::GuiGrid() {}
GuiGrid::GuiGrid(std::string name) {
	mName = name;
	SetColumns(1);

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
	int w = mColumns;
	int h = ceil(mControls.size() / mColumns);
	float wd = mDimension.x / w;
	float hd = mDimension.y / h;

	BOOST_FOREACH(GuiControl& gc, mControls) {
		int x = i % w;
		int y = ceil(i / w);

		gc.SetPosition(Engine::Vector2D(mPosition.x + x * wd, mPosition.y + y * hd));
		gc.SetDimension(Engine::Vector2D(wd, hd));
		++i;
	}
}

void GuiGrid::SetColumns(int columns) {
	mColumns = columns;
	PlaceChildren();
}

int GuiGrid::GetColumns() const {
	return mColumns;
}


}
