#include <iostream>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#include "PlayState.hpp"
#include "Root.hpp"
#include "GuiButton.hpp"
#include "GuiCheckbox.hpp"
#include "Entity.hpp"

PlayState::PlayState() {}

PlayState::~PlayState() {}

void PlayState::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing PlayState.");

    // load resources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();
	resmgr->AddImage(boost::filesystem::path("../game/gfx"),
					 "submarine1.svg", 80, 53, "submarine");
    resmgr->AddImage(boost::filesystem::path("../game/gfx"),
					 "aim.svg", 80, 53, "aim");
    resmgr->AddImage(boost::filesystem::path("../game/gfx"),
					 "torpedo1.svg", 80, 53, "torpedo");
    resmgr->AddImage(boost::filesystem::path("../game/gfx"),
					 "missing.svg", 80, 53, "missing");
    resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "button.svg", 24, 24, "gui.button");
    resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "button_hover.svg", 24, 24, "gui.button_hover");
                     
    sf::Font font;
    font.LoadFromFile("../game/fonts/kingthings_trypewriter_2.ttf");
    resmgr->AddFont(font, "default");
    
    // create GUI
	// TODO: Do stuff

	// client side only entity
    mCrosshair = new Crosshair();
    AddEntity(mCrosshair);
    
    // Add some GUI
    CreateGuiSystem();
    Engine::GuiButton* c = new Engine::GuiButton("waiting");
    c->SetDimension(Engine::Vector2D(200,30));
    c->SetPosition(Engine::Vector2D(20,20));
    c->SetText("Server did not answer yet...");
    c->SetFont(Engine::Root::get_mutable_instance().GetResourceManagerPtr()->GetFont("default"));
    c->SetFontSize(12);
    c->BindOnClick(boost::bind(&PlayState::ExitButton_OnClick, this, _1, _2, _3)); // bind test signal ;)
    mGuiSystems.begin()->AddControl(c);
    

    auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
    // bind keys
    Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnLeaveGame, this);
    inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
    // bind mouse
    Engine::MouseBindingCallback mcb = boost::bind(&PlayState::OnClick, this, _1);
    inputmgr->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
    Engine::MouseBindingCallback right = boost::bind(&PlayState::OnRightClick, this, _1);
    inputmgr->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

    // mouse cursor
    Engine::MouseBindingCallback mv = boost::bind(&PlayState::OnMouseMove, this, _1);
    inputmgr->BindMouse(mv, Engine::MOUSE_MOVED);
    // hide original cursor
    Engine::Root::get_mutable_instance().SetMouseHidden(true);
    
    // Bind connection events
    auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
    netmgr->BindOnClientConnected(boost::bind(&PlayState::OnClientConnected, this, _1));
}

void PlayState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down PlayState.");
}

void PlayState::Update(float time_delta) {
    UpdateAllEntities(time_delta);
}

void PlayState::OnSetNoisyMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position) {	
    // get the player submarine
    /*BOOST_FOREACH(Engine::Entity& entity, mEntities){
        if (entity.GetClientId() == Engine::Root::get_mutable_instance().GetClientId()){
            mPlayerSubmarine = (Submarine*)&entity;
        }
     }

    
    sf::Packet p;
    p << sf::Uint16(Engine::NETCMD_ENTITYACTION) << 0x01 << mPlayerSubmarine->GetUniqueId() << mouse_position.X << mouse_position.Y;
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(p);
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_STATE, "Sent entity action for navigation of submarine.");
    * */
}

void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position) {
    /*const Engine::Vector2D target = Engine::Vector2D(mouse_position.X, mouse_position.Y);
    Torpedo* torpedo = (Torpedo*)mPlayerSubmarine->FireTorpedoTo(target);
    AddEntity(torpedo);*/
}

void PlayState::OnLeaveGame() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Quitting game.");
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_NETWORK, "Sending packet with NETCMD_CLIENTQUIT.");

	// Send NETCMD_CLIENTQUIT to server
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();

    Engine::Root::get_mutable_instance().RequestShutdown();
}

void PlayState::OnClick(Engine::MouseEventArgs args) {
    OnNavigateTo(args);
    Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendChatMessage("I am so glad I just clicked!");
}

void PlayState::OnRightClick(Engine::MouseEventArgs args) {
    OnFireTorpedo(args);
}

void PlayState::OnMouseMove(Engine::MouseEventArgs args) {
    mCrosshair->SetPosition(args.X, args.Y);
}

void PlayState::OnClientConnected(const std::string& client_name) {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "CLient connected: " + client_name);
    if (client_name == Engine::Root::get_mutable_instance().GetClientName()){
        logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "THAT'S YOU!!");
        // TODO: Unpause StateManager.
        mGuiSystems.begin()->GetControl<Engine::GuiButton>("waiting")->SetText("Found Server!");
    }
}

void PlayState::ExitButton_OnClick(const sf::Uint16 mouse_x, const sf::Uint16 mouse_y, const sf::Uint16 mouse_button) {
    auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Yeah you clicked on that nice button which will not cause anything to happen as it has been abused as a label ;)");
}
