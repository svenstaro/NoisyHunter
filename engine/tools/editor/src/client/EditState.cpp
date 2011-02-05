#include <iostream>

#include "EditState.hpp"
#include "PauseState.hpp"
#include "Root.hpp"

EditState::EditState() {}

EditState::~EditState() {}

void EditState::Pause() {
	if(IsCurrentState())
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PauseState());
}

void EditState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing EditState.");

	// Loading Recources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	boost::filesystem::path gfx("../engine/tools/editor/gfx");
	resmgr->AddImage(gfx, "tileset.png", 2, 4);

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

		/*
		// Exit button
		Engine::GuiButton* c = new Engine::GuiButton("menu_button");
		c->SetDimension(Engine::Vector2D(100,40));
		c->SetPosition(Engine::Vector2D(5,555));
		c->SetText("Show Menu");
		c->SetFontColor(sf::Color::White);
		//c->BindOnClick(boost::bind(&EditState::MenuButton_OnClick, this, _1));
		mGuiSystems.begin()->AddControl(c);
		*/


	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	// bind keys
	Engine::KeyBindingCallback cb = boost::bind(&EditState::OnPressEscape, this);
	inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
	/*
	// screenshot
	Engine::KeyBindingCallback sscb = boost::bind(&PlayState::OnScreenshot, this);
	inputmgr->BindKey( sscb, Engine::KEY_PRESSED, sf::Key::F5 );
	// hide original cursor
	Engine::Root::get_mutable_instance().SetMouseHidden(true);*/

	// Bind connection events
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->BindOnClientConnected(boost::bind(&EditState::OnClientConnected, this, _1));

	// Connect To Server
	netmgr->SetEntityState(this);
	netmgr->ConnectToServer();

	AddLocalEntity(new Grid());
}

void EditState::Shutdown() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Shutting down EditState.");
	Engine::Logger::Debug(Engine::LogOrigin::NETWORK, "Sending packet with NETCMD_CLIENTQUIT.");

	// Send NETCMD_CLIENTQUIT to server
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();
}

void EditState::Update(float time_delta) {
    UpdateAllEntities(time_delta);
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("ping_label")->SetText("Ping: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->GetPing()));
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("fps_label")->SetText("FPS: " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetAverageFps()) + " / " + boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetFps()));
	// TODO: Put this back. We don't know the currently active world so we need to count up all entities from all worlds.
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("entitycount_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityCount()) + " Entities");
	mGuiSystems.begin()->GetControl<Engine::GuiGrid>("debug_grid")->GetControl<Engine::GuiLabel>("entityadded_label")->SetText(boost::lexical_cast<std::string>(Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().GetEntityAdded()) + " Entities");
}

void EditState::OnClientConnected(const sf::Uint16 client_id) {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Client connected: " + boost::lexical_cast<std::string>(client_id));
	if(client_id == Engine::Root::get_mutable_instance().GetClientId()) {
		Engine::Logger::Message(Engine::LogOrigin::STATE, "It has been found that the recently connected player is you.");
        // TODO: Unpause StateManager.
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("info_label")->SetText("Connection successful, found the server!");
    }
}

void EditState::OnPressEscape() {
	Pause();
}

/*void PlayState::MenuButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PauseState());
}*/
