#include "GuiLabel.hpp"

namespace Engine{

GuiLabel::GuiLabel() {}
GuiLabel::GuiLabel(std::string name) {
	mName = name;
	SetFont(sf::Font::GetDefaultFont());
	SetFontSize(12);
	SetFontStyle(sf::Text::Regular);
	SetFontColor(sf::Color::Black);
}
GuiLabel::~GuiLabel() {}

GuiLabel* GuiLabel::clone() const {
	return new GuiLabel();
}


void GuiLabel::SetFont(const sf::Font& font) {
	mText.SetFont(font);
}

void GuiLabel::SetFontSize(const float size) {
	mText.SetCharacterSize(size);
}

void GuiLabel::SetFontStyle(unsigned long style) {
	mText.SetStyle(style);
}

void GuiLabel::SetFontColor(const sf::Color& color) {
	mText.SetColor(color);
}


void GuiLabel::Draw(sf::RenderTarget* target, Vector2D offset) {
	mText.SetString(mCaption);
	mText.SetPosition(mPosition.x + offset.x, mPosition.y + offset.y);

	target->Draw(mText);

	DrawAllAttachments(target);
}

}
