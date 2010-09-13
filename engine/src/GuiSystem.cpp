#include "GuiSystem.hpp"

#include <boost/foreach.hpp>

namespace Engine{

GuiSystem::GuiSystem() {}
GuiSystem::~GuiSystem() {}

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

    if (e.Type == sf::Event::KeyPressed and e.Key.Code == sf::Key::Tab){
        bool back = e.Key.Shift;
        // focus next / prev element

        boost::ptr_vector<GuiControl>::iterator i;
        for (i = mControls.begin(); i != mControls.end(); i++) {
            if (i->HasFocus()){
                if (back) i--;
                else i++;
                if (i == mControls.end()) SetFocus( &(mControls.front()) );
                else if (i == mControls.begin()) SetFocus( &(mControls.back()) );
                else SetFocus( &(*i) );
                break;
            }
        }

    }


    BOOST_FOREACH(GuiControl& control, mControls){

        if (e.Type == sf::Event::MouseButtonPressed){
            if (control.IsAtPoint(Vector2D(e.MouseButton.X,e.MouseButton.Y))){
                SetFocus(&control);

                if (e.MouseButton.Button == sf::Mouse::Left)
                    control.OnClick();
                else if (e.MouseButton.Button == sf::Mouse::Right)
                    control.OnRightClick();
            }
        }
        else if (e.Type == sf::Event::KeyPressed and control.HasFocus()){
            control.OnKeyDown(e.Key.Code);
        }
        else if (e.Type == sf::Event::TextEntered and control.HasFocus()){
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
