#include <iostream>

#include "MenuState.hpp"
#include "Root.hpp"

MenuState::MenuState() {}

MenuState::~MenuState() {}

void MenuState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing MenuState.");

	// NICE PARTICLES
	Engine::ParticleSystem* part_sys;
	part_sys = new Engine::ParticleSystem();
	part_sys->SetPosition(Engine::Vector2D(0,650));
	part_sys->SetDirection(Engine::Vector2D(0.f, -1.f));
	part_sys->SetPositionType(Engine::Entity::PositionType::POSITIONTYPE_WORLDPIXEL);

	Engine::ParticleEmitter* part_emit;

	for(int i = 0; i <= 3; ++i) {
		part_emit = new Engine::ParticleEmitter();
		part_emit->SetPositionOffset(Engine::Vector2D(100.f + i * 200, 0.f));
		part_emit->SetRotationOffset(0.f);
		part_emit->SetSpeed(60.f);
		part_emit->SetSpread(20.f);
		part_emit->SetRate(1.7f);
		part_emit->SetTimeToLive(10.f);
		part_emit->SetStartScale(0.5f);
		part_emit->SetEndScale(2.f);
		part_emit->SetStartAlpha(180);
		part_emit->SetEndAlpha(0);
		part_emit->SetImageName("particle_bubble");
		part_emit->SetEndColor(sf::Color(0,0,255));
		part_sys->AddEmitter(part_emit);
	}

	AddLocalEntity(part_sys);

	// Add GUI
	CreateGuiSystem();

	// Gui grid for buttons
	Engine::GuiGrid* grid = new Engine::GuiGrid("debug_grid");
	grid->SetDimension(Engine::Vector2D(160, 160));
	grid->SetPosition(10, 10);

		// Play Button
		Engine::GuiButton* play = new Engine::GuiButton("play_button");
		//play->SetDimension(Engine::Vector2D(200,40));
		//c->SetPosition(Engine::Vector2D(5,555));
		play->SetText("Play now on localhorst");
		play->SetFontColor(sf::Color::White);
		play->BindOnClick(boost::bind(&MenuState::PlayButton_OnClick, this, _1));
		grid->AddControl(play);

		// Start server Button
		Engine::GuiButton* server = new Engine::GuiButton("server_button");
		//server->SetDimension(Engine::Vector2D(200,40));
		//c->SetPosition(Engine::Vector2D(5,555));
		server->SetText("Start a server");
		server->SetFontColor(sf::Color::White);
		server->BindOnClick(boost::bind(&MenuState::StartServerButton_OnClick, this, _1));
		grid->AddControl(server);

		// Options Button
		Engine::GuiButton* options = new Engine::GuiButton("options_button");
		//play->SetDimension(Engine::Vector2D(200,40));
		//c->SetPosition(Engine::Vector2D(5,555));
		options->SetText("Options");
		options->SetFontColor(sf::Color::White);
		options->BindOnClick(boost::bind(&MenuState::OptionsButton_OnClick, this, _1));
		grid->AddControl(options);

		// Quit Button
		Engine::GuiButton* quit = new Engine::GuiButton("quit_button");
		//play->SetDimension(Engine::Vector2D(200,40));
		//c->SetPosition(Engine::Vector2D(5,555));
		quit->SetText("Quit game");
		quit->SetFontColor(sf::Color::White);
		quit->BindOnClick(boost::bind(&MenuState::QuitButton_OnClick, this, _1));
		grid->AddControl(quit);

	mGuiSystems.begin()->AddControl(grid);


	/*
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
	Engine::GuiTextfield* t = new Engine::GuiTextfield("chat_textfield");
	t->SetDimension(Engine::Vector2D(400,25));
	t->SetPosition(Engine::Vector2D(395,555));
	t->SetText("Enter text here");
	t->SetFontColor(sf::Color::White);
	mGuiSystems.begin()->AddControl(t);
	*/

	// bind keys
	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	Engine::KeyBindingCallback cb = boost::bind(&MenuState::OnPressEscape, this);
	inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );

	Radar* radar = new Radar();
	radar->Initialize();
	AddLocalEntity(radar);

	auto musicmgr = Engine::Root::get_mutable_instance().GetMusicManagerPtr();
	musicmgr->Play("TheAstronomer.ogg");
}

void MenuState::Shutdown() {
	Engine::Logger::Debug(Engine::LogOrigin::STATE, "Shutting down MenuState.");
}

void MenuState::Update(float time_delta) {
	UpdateAllEntities(time_delta);
}

void MenuState::OnPressEscape() {
	if(IsCurrentState())
		Engine::Root::get_mutable_instance().RequestShutdown();
}

void MenuState::PlayButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PlayState());
}

void MenuState::StartServerButton_OnClick(const sf::Uint16 mouse_button) {

}

void MenuState::OptionsButton_OnClick(const sf::Uint16 mouse_button) {

}

void MenuState::QuitButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().RequestShutdown();
}
