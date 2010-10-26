#include <iostream>

#include "PlayState.hpp"
#include "Root.hpp"

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
					 "torpedo1.svg", 30, 10, "torpedo");
    resmgr->AddImage(boost::filesystem::path("../game/gfx"),
					 "missing.svg", 80, 53, "missing");
    resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "button.svg", 48, 48, "gui.button");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "button_hover.svg", 48, 48, "gui.button_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "button_focus.svg", 48, 48, "gui.button_focus");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "textfield2.svg", 24, 24, "gui.textfield");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "progressbar_back.svg", 24, 24, "gui.progressbar_back");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
					 "progressbar_front.svg", 24, 24, "gui.progressbar_front");

	sf::Font font;
	font.LoadFromFile("../game/fonts/kingthings_trypewriter_2.ttf");
	resmgr->AddFont(font, "trypewriter");
	resmgr->AddFont(font, "default");
	//resmgr->AddFont(sf::Font::GetDefaultFont(), "default");

	// create GUI
	// TODO: Do stuff

	// client side only entity
	mCrosshair = new Crosshair();
	AddEntity(mCrosshair);

	// Add some GUI
	CreateGuiSystem();

		// Info Label
		Engine::GuiLabel* l = new Engine::GuiLabel("info_label");
		l->SetPosition(5,5);
		l->SetText("Connecting to server...");
		l->SetFont(sf::Font::GetDefaultFont());
		l->SetFontSize(11);
		l->SetFontStyle(sf::Text::Regular);
		l->SetFontColor(sf::Color::White);
		mGuiSystems.begin()->AddControl(l);

		// Ping info Label
		Engine::GuiLabel* p = new Engine::GuiLabel("ping_label");
		p->SetPosition(750,5);
		p->SetText("0");
		p->SetFont(sf::Font::GetDefaultFont());
		p->SetFontSize(12);
		p->SetFontStyle(sf::Text::Regular);
		p->SetFontColor(sf::Color::White);
		mGuiSystems.begin()->AddControl(p);

		// Exit button
		Engine::GuiButton* o = new Engine::GuiButton("options_button");
		o->SetDimension(Engine::Vector2D(100,40));
		o->SetPosition(Engine::Vector2D(5,520));
		o->SetText("Options");
		o->SetFont(sf::Font::GetDefaultFont());
		o->SetFontSize(11);
		o->SetFontStyle(sf::Text::Regular);
		o->SetFontColor(sf::Color::White);
		o->BindOnClick(boost::bind(&PlayState::ExitButton_OnClick, this, _1)); // bind test signal ;)
		mGuiSystems.begin()->AddControl(o);

		// Exit button
		Engine::GuiButton* c = new Engine::GuiButton("exit_button");
		c->SetDimension(Engine::Vector2D(100,40));
		c->SetPosition(Engine::Vector2D(5,555));
		c->SetText("Exit Game");
		c->SetFont(sf::Font::GetDefaultFont());
		c->SetFontSize(11);
		c->SetFontStyle(sf::Text::Regular);
		c->SetFontColor(sf::Color::White);
		c->BindOnClick(boost::bind(&PlayState::ExitButton_OnClick, this, _1));
		mGuiSystems.begin()->AddControl(c);

		// Chat Textfield
		Engine::GuiTextfield* t = new Engine::GuiTextfield("chat_textfield");
		t->SetDimension(Engine::Vector2D(400,25));
		t->SetPosition(Engine::Vector2D(395,555));
		t->SetText("Enter text here");
		t->SetFont(sf::Font::GetDefaultFont());
		t->SetFontSize(11);
		t->SetFontColor(sf::Color::White);
		mGuiSystems.begin()->AddControl(t);

		// Test progress bar
		Engine::GuiProgressbar* b = new Engine::GuiProgressbar("test_bar");
		b->SetPosition(Engine::Vector2D(50,50));
		b->SetDimension(Engine::Vector2D(300,30));
		b->SetProgress(0.3);
		b->SetFontSize(11);
		mGuiSystems.begin()->AddControl(b);

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
	mGuiSystems.begin()->GetControl<Engine::GuiLabel>("ping_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->GetPing()));
}

void PlayState::OnSetNoisyMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode() {
    //mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position) {	
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_SETSUBMARINETARGET) << mouse_position.X << mouse_position.Y;
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
}

void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position) {
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_FIRETORPEDO) << mouse_position.X << mouse_position.Y;
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
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
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("info_label")->SetText("Connection successful, found the server!");
    }
}

void PlayState::ExitButton_OnClick(const sf::Uint16 mouse_button) {
	/*auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Yeah you clicked on that nice button which will not cause anything to happen as it has been abused as a label ;)");*/
	//Engine::Root::get_mutable_instance().RequestShutdown();
	OnLeaveGame();
}
