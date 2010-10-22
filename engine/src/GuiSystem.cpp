#include "GuiSystem.hpp"

#include <boost/foreach.hpp>
#include <iostream>

namespace Engine{

GuiSystem::GuiSystem() {}

GuiSystem::~GuiSystem() {}

GuiSystem* GuiSystem::clone() const {
	return new GuiSystem();
}

void GuiSystem::SetFocus(GuiControl* control){
    BOOST_FOREACH(GuiControl& c, mControls){
        c.SetFocus(false);
    }
    control->SetFocus(true);
}

void GuiSystem::Update(const float time_delta) {
    BOOST_FOREACH(GuiControl& control, mControls){
        control.Update(time_delta);
    }
}

void GuiSystem::HandleEvent(sf::Event e) {
    if(e.Type == sf::Event::KeyPressed and e.Key.Code == sf::Key::Tab) {
        bool back = e.Key.Shift;
        // focus next / prev element

        boost::ptr_vector<GuiControl>::iterator i;
        for(i = mControls.begin(); i != mControls.end(); i++) {
            if(i->HasFocus()) {
                if(back)
                    i--;
                else
                    i++;

                if(i == mControls.end())
                    SetFocus( &(mControls.front()) );
                else if(i == mControls.begin())
                    SetFocus( &(mControls.back()) );
                else
                    SetFocus( &(*i) );
                break;
            }
        }

    }

    BOOST_FOREACH(GuiControl& control, mControls) {
		if(e.Type == sf::Event::MouseButtonPressed || e.Type == sf::Event::MouseButtonReleased) {
            if(control.IsAtPoint(Vector2D(e.MouseButton.X,e.MouseButton.Y))) {
                SetFocus(&control);
                                
                // non-default buttons (extra buttons on mouse) will not become "0"
                sf::Uint16 mouse_button = 0;
                
                if(e.MouseButton.Button == sf::Mouse::Left)
                    mouse_button = 1;
                else if(e.MouseButton.Button == sf::Mouse::Middle)
                    mouse_button = 2;
                else if(e.MouseButton.Button == sf::Mouse::Right)
                    mouse_button = 3;

				if(e.Type == sf::Event::MouseButtonPressed) {
					control.OnMouseDown(e.MouseButton.X, e.MouseButton.Y, mouse_button);
					control.TriggerOnMouseDown(e.MouseButton.X, e.MouseButton.Y, mouse_button);
				} else { // MouseButtonReleased
					control.OnMouseUp(e.MouseButton.X, e.MouseButton.Y, mouse_button);
					control.TriggerOnMouseUp(e.MouseButton.X, e.MouseButton.Y, mouse_button);
				}
            }
        } else if(e.Type == sf::Event::KeyPressed and control.HasFocus()) {
            control.OnKeyDown(e.Key.Code);
            control.TriggerOnKeyDown(e.Key.Code);
        } else if(e.Type == sf::Event::KeyReleased and control.HasFocus()) {
            control.OnKeyUp(e.Key.Code);
            control.TriggerOnKeyUp(e.Key.Code);
        } else if(e.Type == sf::Event::TextEntered and control.HasFocus()) {
            control.OnType(e.Text.Unicode);
            control.TriggerOnType(e.Text.Unicode);
        }
        
        if(e.Type == sf::Event::MouseMoved) {
            bool hover = control.IsAtPoint(Vector2D(e.MouseMove.X, e.MouseMove.Y));
            control.SetHover(hover);
            if(hover) {
                control.OnMouseMove(e.MouseMove.X, e.MouseMove.Y);
                control.TriggerOnMouseMove(e.MouseMove.X, e.MouseMove.Y);
            }
        }

    }

}

void GuiSystem::Draw(sf::RenderTarget* target) {
    BOOST_FOREACH(GuiControl& control, mControls){
        control.Draw(target);
    }
}

void GuiSystem::AddControl(GuiControl* control) {
    mControls.push_back(control);
}

}
