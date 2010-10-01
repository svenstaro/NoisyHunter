#ifndef GUICONTROL_HPP
#define GUICONTROL_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Vector2D.hpp"

namespace Engine{

class GuiControl : public Entity {
public:
    GuiControl(const sf::Uint16 unique_id = 0, 
			   const std::string& name = "undefined");

    ~GuiControl();

    // main callbacks
    virtual void Update(const float time_delta);

    virtual void Draw(sf::RenderTarget* target);

    // event callbacks
    virtual void OnType(sf::Uint32 unicode_char);

    virtual void OnClick();

    virtual void OnRightClick();

    virtual void OnKeyDown(sf::Key::Code key_code);

	virtual sf::Uint16 GetEntityId() const;

    // needed for hover and mouse events
    virtual bool IsAtPoint(const Vector2D point);

    // setter for hover and focus
    void SetFocus(bool is_focused = true);

    bool HasFocus() const;

    void SetHover(bool hover = true);

    // set screen position type
    Entity::PositionType GetPositionType() const;

    void SetPosition(const Vector2D position);

    const Vector2D GetPosition() const;

    void SetDimension(const Vector2D dimension);

    const Vector2D GetDimension() const;

    void SetText(std::string text);

    const std::string GetText() const;

    const std::string GetName() const;

protected:
    std::string mName;
    std::string mText;
    bool mIsFocused;
    bool mHover;

    Vector2D mPosition;
    Vector2D mDimension;
};

}

#endif
