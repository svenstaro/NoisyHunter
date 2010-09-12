#include "LoadingState.hpp"

#include "Root.hpp"
#include "GuiButton.hpp"
#include "GuiCheckbox.hpp"

LoadingState::LoadingState() {}
LoadingState::~LoadingState() {}

// state control
void LoadingState::Initialize() {
    // load gui resources

    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gui"),"button.svg",             100, 100, "gui.button");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gui"),"button_hover.svg",       100, 100, "gui.button_hover");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gui"),"checkbox.svg",           16, 16, "gui.checkbox");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gui"),"checkbox_checked.svg",   16, 16, "gui.checkbox_checked");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddImage(boost::filesystem::path("../game/gui"),"checkbox_hover.svg",     16, 16, "gui.checkbox_hover");

    // load font
    sf::Font font;
    font.LoadFromFile("../game/fonts/kingthings_trypewriter_2.ttf");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddFont(font, "default");


    // create gui
    CreateGuiSystem();

    Engine::GuiButton* c = new Engine::GuiButton("test");
    c->SetDimension(Engine::Vector2D(100,30));
    c->SetPosition(Engine::Vector2D(20,20));
    c->SetText("Play!");
    c->SetFont(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetFont("default"));
    mGuiSystems.begin()->AddControl(c);

    Engine::GuiCheckbox* b = new Engine::GuiCheckbox("test");
    b->SetPosition(Engine::Vector2D(20,60));
    b->SetText("Click me to check me ;)");
    b->SetFont(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetFont("default"));
    b->SetFontColor(sf::Color(255,255,255));
    mGuiSystems.begin()->AddControl(b);

    // (create entities)

    // bind input events
    Engine::InputManager* in = Engine::Root::get_mutable_instance().GetInputManagerPtr();

    Engine::KeyBindingCallback cb = boost::bind(&LoadingState::OnAnyKeyPressed, this);
    in->BindKey( cb, Engine::KEY_PRESSED);

    /*// bind mouse
    Engine::MouseBindingCallback mcb = boost::bind(&PlayState::OnClick, this, _1);
    in->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
    Engine::MouseBindingCallback right = boost::bind(&PlayState::OnRightClick, this, _1);
    in->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

    // mouse cursor
    Engine::MouseBindingCallback mv = boost::bind(&PlayState::OnMouseMove, this, _1);
    in->BindMouse(mv, Engine::MOUSE_MOVED);

    */
    // hide cursor
    //Engine::Root::get_mutable_instance().SetMouseHidden(true);

}
void LoadingState::Shutdown() {}
//void Update(float time_delta);

void LoadingState::OnCancel() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
void LoadingState::OnClick(Engine::MouseEventArgs args) {
    // load playstate if finished loading
}
void LoadingState::OnAnyKeyPressed() {
    // load playstate if finished loading
    //std::cout << "pressed" << std::endl;
}
