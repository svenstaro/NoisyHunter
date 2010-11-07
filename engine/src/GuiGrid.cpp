#include "GuiGrid.hpp"

#include "Root.hpp"

namespace Engine{

GuiGrid::GuiGrid() {}
GuiGrid::GuiGrid(std::string name) {
	mName = name;
	mImage = Root::get_mutable_instance().GetResourceManagerPtr()->GetImage("gui.grid");
}
GuiGrid::~GuiGrid() {}

GuiGrid* GuiGrid::clone() const {
	return new GuiGrid();
}

void GuiGrid::Initialize() {
	mSprite.SetImage(mImage);
	mSprite.SetPosition(mPosition.x, mPosition.y);
	mSprite.SetScale(mDimension.x, mDimension.y);
}

void GuiGrid::AddControl(GuiControl* guicontrol) {
	guicontrol->SetPosition(guicontrol->GetPosition()+mPosition + Engine::Vector2D(5, 5));
	mChildren.push_back(guicontrol);
}

void GuiGrid::Draw(sf::RenderTarget* target) {

	target->Draw(mSprite);

	BOOST_FOREACH(GuiControl& gc, mChildren) {
		gc.Draw(target);
	}

	DrawAllAttachments(target);
}

}
