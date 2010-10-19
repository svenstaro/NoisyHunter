#ifndef GUISYSTEM_HPP
#define GUISYSTEM_HPP

#include "GuiControl.hpp"
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/foreach.hpp>

namespace Engine {

class GuiSystem {
public:
    GuiSystem();

    ~GuiSystem();

	GuiSystem* clone() const;

    void Update(const float time_delta);
    void HandleEvent(sf::Event e);
    // Draws all controls to render target.
    void Draw(sf::RenderTarget* target);

    void SetFocus(GuiControl* control);


    void AddControl(GuiControl* control);
    
    template < typename T >
    T* GetControl(const std::string& control_name) {
        BOOST_FOREACH(GuiControl& control, mControls){
            if (control.GetName() == control_name){
                return (T*)&control;
            }
        }
        return NULL;
    }

private:
    // Controls list
    boost::ptr_vector<GuiControl> mControls;

};

}

#endif
