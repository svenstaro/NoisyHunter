#include <iostream>

#include "PlayState.hpp"
#include "Root.hpp"

PlayState::PlayState() {}

PlayState::~PlayState() {}

void PlayState::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing PlayState.");

	// Particle system for cursor
	Engine::Vector2D position = Engine::Vector2D(0.5f, 0.5f);
	Engine::Vector2D direction = Engine::Vector2D(1.f, 1.f);
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem(position, direction, Engine::Entity::PositionType::POSITIONTYPE_WORLD);
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter();
	part_emit->SetRate(100.f);
	part_emit->SetTimeToLive(1.f);
	part_emit->SetStartScale(0.5f);
	part_emit->SetEndScale(3.f);
	part_sys->AddEmitter(part_emit);
	AddEntity(part_sys);
	mCursorPartSys = part_sys;

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
	packet << 3.f; // time_to_live
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
	mCursorPartSys->SetPosition(args.X, args.Y);
	std::cout << mCursorPartSys->GetPosition().x << " " << mCursorPartSys->GetPosition().y << std::endl;
}

void PlayState::OnClientConnected(const sf::Uint16 client_id) {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Client connected: " + boost::lexical_cast<std::string>(client_id));
    if(client_id == Engine::Root::get_mutable_instance().GetClientId()) {
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
