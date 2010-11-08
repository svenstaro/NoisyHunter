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
	Engine::Vector2D direction = Engine::Vector2D(0.f, -2.f);
	Engine::ParticleSystem* part_sys = new Engine::ParticleSystem();
	part_sys->SetPosition(position);
	part_sys->SetDirection(direction);
	part_sys->SetPositionType(Engine::Entity::PositionType::POSITIONTYPE_SCREENPIXEL);
	Engine::ParticleEmitter* part_emit = new Engine::ParticleEmitter();
	part_emit->SetPositionOffset(Engine::Vector2D(0.f, 0.f));
	part_emit->SetRotationOffset(0.f);
	part_emit->SetSpeed(50.f);
	part_emit->SetSpread(360.f);
	part_emit->SetBlendMode(sf::Blend::Add);
	part_emit->SetRate(2000.f);
	part_emit->SetTimeToLive(10.f);
	part_emit->SetStartScale(0.7f);
	part_emit->SetEndScale(1.5f);
	part_emit->SetStartColor(sf::Color(255,255,255));
	part_emit->SetEndColor(sf::Color(64,64,64));
	part_emit->SetStartAlpha(230);
	part_emit->SetEndAlpha(0);
	part_emit->SetImageName("particle_cursor");
	part_sys->AddEmitter(part_emit);
	AddEntity(part_sys);
	mCursorPartSys = part_sys;

	// Add some GUI
	CreateGuiSystem();

		// Info label
		Engine::GuiLabel* l = new Engine::GuiLabel("info_label");
		l->SetPosition(5,5);
		l->SetText("Connecting to server...");
		l->SetFontColor(sf::Color::White);
		mGuiSystems.begin()->AddControl(l);

		// Ping info label
		Engine::GuiLabel* p = new Engine::GuiLabel("ping_label");
		p->SetPosition(5,5);
		p->SetText("0");
		p->SetFontColor(sf::Color::White);

		// FPS info label
		Engine::GuiLabel* f = new Engine::GuiLabel("fps_label");
		f->SetPosition(5,20);
		f->SetText("0");
		f->SetFontColor(sf::Color::White);

		// EntitiyCount info label
		Engine::GuiLabel* ec = new Engine::GuiLabel("entitycount_label");
		ec->SetPosition(5,35);
		ec->SetText("0");
		ec->SetFontColor(sf::Color::White);

		// Group debug labels
		Engine::GuiGrid* grid = new Engine::GuiGrid("debug_grid");
		grid->SetDimension(Engine::Vector2D(90, 70));
		grid->SetPosition(700,10);
		grid->AddControl(p);
		grid->AddControl(f);
		grid->AddControl(ec);
		mGuiSystems.begin()->AddControl(grid);

		// Exit button
		Engine::GuiButton* c = new Engine::GuiButton("menu_button");
		c->SetDimension(Engine::Vector2D(100,40));
		c->SetPosition(Engine::Vector2D(5,555));
		c->SetText("Show Menu");
		c->SetFontColor(sf::Color::White);
		c->BindOnClick(boost::bind(&PlayState::MenuButton_OnClick, this, _1));
		mGuiSystems.begin()->AddControl(c);

		// Chat Textfield
		/*
		Engine::GuiTextfield* t = new Engine::GuiTextfield("chat_textfield");
		t->SetDimension(Engine::Vector2D(400,25));
		t->SetPosition(Engine::Vector2D(395,555));
		t->SetText("Enter text here");
		t->SetFontColor(sf::Color::White);
		mGuiSystems.begin()->AddControl(t);
		*/

	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	// bind keys
	Engine::KeyBindingCallback cb = boost::bind(&PlayState::OnPauseGame, this);
	inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
	// screenshot
	Engine::KeyBindingCallback sscb = boost::bind(&PlayState::OnScreenshot, this);
	inputmgr->BindKey( sscb, Engine::KEY_PRESSED, sf::Key::F5 );
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

	// Connect To Server
	netmgr->SetEntityState(this);
	netmgr->ConnectToServer();

	

}

void PlayState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Shutting down PlayState.");
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_NETWORK, "Sending packet with NETCMD_CLIENTQUIT.");

	// Send NETCMD_CLIENTQUIT to server
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();
}


void PlayState::Update(float time_delta) {
    UpdateAllEntities(time_delta);
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("ping_label")->SetText("Ping: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->GetPing()));
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("fps_label")->SetText("FPS: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetAverageFps()) + " / " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetFps()));
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("entitycount_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityCount()) + " Entities");

	BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
		if (sub->GetClientId() == Engine::Root::get_mutable_instance().GetClientId()) {
			Engine::Root::get_mutable_instance().CenterViewAt(Engine::Coordinates::WorldFloatToWorldPixel(sub->GetPosition()));
		}
	}
}

void PlayState::OnSetNoisyMode() {
//	if(IsCurrentState())
		//mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayState::OnSetSilentMode() {
//	if(IsCurrentState())
		//mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayState::OnNavigateTo(const Engine::Coordinates& mouse_position) {	
	if(IsCurrentState()) {
		sf::Packet packet;
		packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_SETSUBMARINETARGET);
		packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
		Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
	}
}

void PlayState::OnFireTorpedo(const Engine::Coordinates& mouse_position) {
	if(IsCurrentState()) {
		sf::Packet packet;
		packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_FIRETORPEDO);
		packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
		packet << 3.f; // time_to_live
		Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
	}
}

void PlayState::OnFireSonarPing(const Engine::Coordinates& mouse_position) {
	if(IsCurrentState()) {
		sf::Packet packet;
		packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_FIRESONARPING);
		packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
		packet << 5.f;
		Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
	}
}

void PlayState::OnScreenshot() {
	// Set TakeScreenshot in the Root to true so that the main loop knows that it has to take a screenshot.
	// We have to do it there.
	Engine::Root::get_mutable_instance().SetTakeScreenshot(true);
}

void PlayState::OnPauseGame() {
	if(IsCurrentState())
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PauseState());
}

void PlayState::OnClick(Engine::MouseEventArgs args) {
	if(IsCurrentState()) {
		OnNavigateTo(args);
		Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendChatMessage("I am so glad I just clicked!");
	}
}

void PlayState::OnRightClick(Engine::MouseEventArgs args) {
	if(IsCurrentState()) {
		OnFireTorpedo(args);
		OnFireSonarPing(args);
	}
}

void PlayState::OnMouseMove(Engine::MouseEventArgs args) {
	mCursorPartSys->SetPosition(400, 300);
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

void PlayState::MenuButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PauseState());
}
