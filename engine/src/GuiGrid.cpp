#include "GuiGrid.hpp"

namespace Engine{

GuiGrid::GuiGrid() {}
GuiGrid::GuiGrid(std::string name) {
	mName = name;
}
GuiGrid::~GuiGrid() {}

GuiGrid* GuiGrid::clone() const {
	return new GuiGrid();
}

void GuiGrid::AddControl(GuiControl* guicontrol) {
	guicontrol->SetPosition(guicontrol->GetPosition()+mPosition);
	mChildren.push_back(guicontrol);
}

void GuiGrid::Draw(sf::RenderTarget* target) {

	BOOST_FOREACH(GuiControl& gc, mChildren) {
		gc.Draw(target);
	}

	DrawAllAttachments(target);
}

}
