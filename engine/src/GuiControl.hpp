#ifndef GUICONTROL_HPP
#define GUICONTROL_HPP

#include "Entity.hpp"
#include "Vector2D.hpp"

#include <SFML/Graphics.hpp>

namespace Engine{

class GuiControl : public Entity {
public:
    GuiControl(std::string name);
    ~GuiControl();

    // main callbacks
    virtual void Update(const float time_delta);
    virtual void Draw(sf::RenderTarget* target);

    // set screen position type
    Entity::PositionType GetPositionType() const;

    // needed for hover and mouse events
    virtual bool IsAtPoint(const Vector2D point);

    // event callbacks
    virtual void OnType(sf::Uint32 unicode_char);
    virtual void OnClick();
    virtual void OnRightClick();
    virtual void OnKeyDown(sf::Key::Code key_code);



    // setter for hover and focus
    void SetFocus(bool is_focused = true);
    bool HasFocus() const;
    void SetHover(bool hover = true);

    // set / get position
    void SetPosition(const Vector2D position);
    const Vector2D GetPosition() const;

    // set / get dimension
    void SetDimension(const Vector2D dimension);
    const Vector2D GetDimension() const;

    // set / get text
    void SetText(std::string text);
    const std::string GetText() const;

    // set / get name
    const std::string GetName() const;
private:
    std::string mName;
    std::string mText;
    bool mIsFocused;
    bool mHover;

    Vector2D mPosition;
    Vector2D mDimension;
};

}

#endif
