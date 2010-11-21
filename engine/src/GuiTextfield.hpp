#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "GuiLabel.hpp"
#include "TiledSprite.hpp"

namespace Engine{

class GuiTextfield : public GuiLabel {
public:
    GuiTextfield();

    GuiTextfield(std::string name);

    ~GuiTextfield();

	GuiTextfield* create() const;

    // main callbacks
	virtual void Draw(sf::RenderTarget* target);

    void SetMultiline(bool multiline);
    void SetPassword(bool password);

    // event callbacks
	void OnMouseDown();
    void OnKeyDown(sf::Key::Code key_code);
    void OnType(sf::Uint32 unicode_char);
private:
    TiledSprite mSprite;

    int mCursorPosition;
    bool mMultiline;
    bool mHideCharacters;
};

}

#endif
