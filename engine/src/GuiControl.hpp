#ifndef GUICONTROL_HPP
#define GUICONTROL_HPP

#include <boost/signals2.hpp>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Vector2D.hpp"

namespace Engine{

class GuiControl : public Entity {
public:
    GuiControl(const sf::Uint16 entity_unique_id = 0, 
			   const std::string& name = "undefined");

    virtual ~GuiControl() = 0;

	virtual GuiControl* create() const = 0;

    // Main callbacks
    virtual void Update(const float time_delta);
	virtual void Draw(sf::RenderTarget* target) = 0;

    // Event signal binding
	virtual void BindOnMouseDown(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)>::slot_type& slot);
	virtual void BindOnMouseUp(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)>::slot_type& slot);
    virtual void BindOnMouseMove(const boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y)>::slot_type& slot);
    virtual void BindOnKeyDown(const boost::signals2::signal<void (const sf::Key::Code key)>::slot_type& slot);
    virtual void BindOnKeyUp(const boost::signals2::signal<void (const sf::Key::Code key)>::slot_type& slot);
    virtual void BindOnType(const boost::signals2::signal<void (const sf::Uint32 unicode_char)>::slot_type& slot);

    // Event signal triggers
	virtual void TriggerOnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
	virtual void TriggerOnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
    virtual void TriggerOnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y);
    virtual void TriggerOnKeyDown(const sf::Key::Code key);
    virtual void TriggerOnKeyUp(const sf::Key::Code key);
    virtual void TriggerOnType(const sf::Uint32 unicode_char);
    
    // Event callbacks for internal use
	virtual void OnMouseDown(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
	virtual void OnMouseUp(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button);
    virtual void OnMouseMove(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y);
    virtual void OnKeyDown(const sf::Key::Code key);
    virtual void OnKeyUp(const sf::Key::Code key);
    virtual void OnType(const sf::Uint32 unicode_char);
    

	virtual sf::Uint16 GetEntityTypeId() const;

    // needed for hover and mouse events
    virtual bool IsAtPoint(const Vector2D point);

    // setter for hover and focus
    void SetFocus(bool is_focused = true);

    bool HasFocus() const;

	void SetHover(bool hover = true);

    const Vector2D GetPosition() const;

    void SetDimension(const Vector2D dimension);

    const Vector2D GetDimension() const;

    void SetText(std::string text);

    const std::string GetText() const;

    const std::string GetName() const;

	Entity::PositionType GetPositionType() const;

	void SetPositionType(Entity::PositionType position_type);

protected:
    // signals
	boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)> mOnMouseDownSignal;
	boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button)> mOnMouseUpSignal;
    boost::signals2::signal<void (const sf::Uint16 mouse_x, const sf::Uint16 mouse_y)> mOnMouseMoveSignal;
    boost::signals2::signal<void (const sf::Key::Code key)> mOnKeyDownSignal;
    boost::signals2::signal<void (const sf::Key::Code key)> mOnKeyUpSignal;
    boost::signals2::signal<void (const sf::Uint32 unicode_char)> mOnTypeSignal;
    
	std::string mName;
	std::string mCaption;
    bool mIsFocused;
    bool mHover;

    Vector2D mDimension;
	PositionType mPositionType;
};

}

#endif
