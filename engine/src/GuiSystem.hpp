#ifndef GUISYSTEM_HPP
#define GUISYSTEM_HPP

#include "GuiControl.hpp"
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

namespace Engine{


class GuiSystem{
public:
    GuiSystem();
    ~GuiSystem();

    void Update(const float time_delta);
    void HandleEvent(sf::Event e);
    // Draws all controls to render target.
    void Draw(sf::RenderTarget* target);


    void AddControl(GuiControl* control);

private:
    // Controls list
    boost::ptr_vector<GuiControl> mControls;

};


}


#endif
