#include "GuiSystem.hpp"

#include <boost/foreach.hpp>

namespace Engine{

GuiSystem::GuiSystem() {}
GuiSystem::~GuiSystem() {}
void GuiSystem::Update(const float time_delta) {
    BOOST_FOREACH(GuiControl& control, mControls){
        control.Update(time_delta);
    }
}
void GuiSystem::HandleEvent(sf::Event e) {



    BOOST_FOREACH(GuiControl& control, mControls){

        if (e.Type == sf::Event::MouseButtonPressed){
            if (control.IsAtPoint(Vector2D(e.MouseButton.X,e.MouseButton.Y))){
                if (e.MouseButton.Button == sf::Mouse::Left)
                    control.OnClick();
                else if (e.MouseButton.Button == sf::Mouse::Right)
                    control.OnRightClick();
            }
        }
        else if (e.Type == sf::Event::KeyPressed){
            control.OnKeyDown(e.Key.Code);
        }
        else if (e.Type == sf::Event::TextEntered && control.HasFocus()){
            control.OnType(e.Text.Unicode);
        }

        if (e.Type == sf::Event::MouseMoved){
            control.SetHover(control.IsAtPoint(Vector2D(e.MouseMove.X, e.MouseMove.Y)));
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
