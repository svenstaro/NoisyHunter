#include <iostream>

#include "PlayState.hpp"
#include "Root.hpp"

PlayState::PlayState() {}

PlayState::~PlayState() {}

void PlayState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing PlayState.");

	// Particle system for cursor
	/*
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
	part_emit->SetRate(100.f);
	part_emit->SetTimeToLive(6.f);
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
	*/

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

		// EntitiyCount info label
		Engine::GuiLabel* ea = new Engine::GuiLabel("entityadded_label");
		ea->SetPosition(5,50);
		ea->SetText("0");
		ea->SetFontColor(sf::Color::White);

		// Group debug labels
		Engine::GuiGrid* grid = new Engine::GuiGrid("debug_grid");
		grid->SetDimension(Engine::Vector2D(90, 70));
		grid->SetPosition(700,10);
		grid->AddControl(p);
		grid->AddControl(f);
		grid->AddControl(ec);
		grid->AddControl(ea);
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
	// hide original cursor
	Engine::Root::get_mutable_instance().SetMouseHidden(true);

	// Bind connection events
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->BindOnClientConnected(boost::bind(&PlayState::OnClientConnected, this, _1));

	// Connect To Server
	netmgr->SetEntityState(this);
	netmgr->ConnectToServer();

	auto musicmgr = Engine::Root::get_mutable_instance().GetMusicManagerPtr();
	musicmgr->Play("The Island.flac");
}

void PlayState::Shutdown() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Shutting down PlayState.");
	Engine::Logger::Debug(Engine::LogOrigin::NETWORK, "Sending packet with NETCMD_CLIENTQUIT.");

	// Send NETCMD_CLIENTQUIT to server
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();

	auto musicmgr = Engine::Root::get_mutable_instance().GetMusicManagerPtr();
	musicmgr->Stop();
}

void PlayState::Update(float time_delta) {
    UpdateAllEntities(time_delta);
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("ping_label")->SetText("Ping: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->GetPing()));
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("fps_label")->SetText("FPS: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetAverageFps()) + " / " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetFps()));
	// TODO: Put this back. We don't know the currently active world so we need to count up all entities from all worlds.
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("entitycount_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityCount()) + " Entities");
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("entityadded_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityAdded()) + " Entities");
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

void PlayState::OnClientConnected(const sf::Uint16 client_id) {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Client connected: " + boost::lexical_cast<std::string>(client_id));
	if(client_id == Engine::Root::get_mutable_instance().GetClientId()) {
		Engine::Logger::Message(Engine::LogOrigin::STATE, "It has been found that the recently connected player is you.");
        // TODO: Unpause StateManager.
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("info_label")->SetText("Connection successful, found the server!");
    }
}

void PlayState::MenuButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PauseState());
}
