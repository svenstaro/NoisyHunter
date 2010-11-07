#include "GuiGrid.hpp"

#include "Root.hpp"

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
	mChildren.push_back(guicontrol);
}

void GuiGrid::Draw(sf::RenderTarget* target, Vector2D offset) {
	mSprite.SetImage(Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.grid"));
	mSprite.SetPosition(mPosition.x + offset.x, mPosition.y + offset.y);
	mSprite.SetScale(mDimension.x, mDimension.y);

	target->Draw(mSprite);

	BOOST_FOREACH(GuiControl& gc, mChildren) {
		gc.Draw(target, offset + mPosition);
	}

	DrawAllAttachments(target);
}

}
