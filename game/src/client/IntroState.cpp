#include "IntroState.hpp"

#include "Root.hpp"

IntroState::IntroState() {}
IntroState::~IntroState() {}

// state control
void IntroState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing IntroState.");

	mFinishedLoading = false;

	// load resources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	// GUI
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button.svg", 0.48f, 0.48f, "gui.button");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_hover.svg",	0.48f,	0.48f,	"gui.button_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_focus.svg", 0.48f, 0.48f,	"gui.button_focus");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"grid.svg", 0.48f, 0.48f, "gui.grid");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox.svg", 0.16f, 0.16f, "gui.checkbox");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox_checked.svg", 0.16f, 0.16f, "gui.checkbox_checked");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox_hover.svg", 0.16f, 0.16f, "gui.checkbox_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"textfield2.svg", 0.24f, 0.24f, "gui.textfield");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"progressbar_back.svg", 0.24f, 0.24f, "gui.progressbar_back");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"progressbar_front.svg", 0.24f, 0.24f, "gui.progressbar_front");

	// IMAGES
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"submarine1.svg", 0.8f, 0.53f, "submarine");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"submarine_target.svg", 0.2f,	0.2f,	"submarine_target");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"sonarping.svg", 0.2f, 0.2f, "sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"torpedo1.svg", 0.3f, 0.1f, "torpedo");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"missing.svg", 0.8f, 0.53f, "missing");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle1.svg", 0.24f, 0.24f, "particle1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_cursor.svg", 0.24f,	0.24f, "particle_cursor");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_bubble.svg", 0.24f, 0.24f, "particle_bubble");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_sonarping.svg", 0.4f, 0.4f, "particle_sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"glow1.svg", 0.5f, 0.5f, "glow1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"torpedo_trail.svg", 0.24f, 0.24f, "torpedo_trail");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"radar1.svg", 0.875f, 2.5f, "radar1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"radar_background.svg", 5.f, 5.f, "radar_background");

    // load font
    sf::Font font;
    font.LoadFromFile("../game/fonts/kingthings_trypewriter_2.ttf");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddFont(font, "default");
    font.LoadFromFile("../game/fonts/ParmaPetit-Normal.ttf");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddFont(font, "serif");

    // create gui
    CreateGuiSystem();

	Engine::GuiProgressbar* p = new Engine::GuiProgressbar("loading_progress");
	p->SetPosition(Engine::Vector2D(200,575));
	p->SetDimension(Engine::Vector2D(400,10));
	p->SetTextVisible(false);
	mGuiSystems.begin()->AddControl(p);

	Engine::GuiLabel* l = new Engine::GuiLabel("loading_progress_label");
	l->SetPosition(200,560);
	l->SetText("Loading images...");
	l->SetFontSize(11);
	l->SetFontColor(sf::Color::White);
	mGuiSystems.begin()->AddControl(l);

	// register music
	auto musicmgr = Engine::Root::get_mutable_instance().GetMusicManagerPtr();
	musicmgr->Register("../game/music", "TheAstronomer.ogg");
	musicmgr->Register("../game/music", "The Island.flac");
	musicmgr->Play("TheAstronomer.ogg");

    // (create entities)

    // bind input events
    Engine::InputManager* in = Engine::Root::get_mutable_instance().GetInputManagerPtr();

	Engine::KeyBindingCallback cb = boost::bind(&IntroState::OnAnyKeyPressed, this);
    in->BindKey( cb, Engine::KEY_PRESSED);


	/*// bind mouse

	Engine::MouseBindingCallback mcb = boost::bind(&IntroState::OnClick, this, _1);
	in->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
	Engine::MouseBindingCallback right = boost::bind(&IntroState::OnRightClick, this, _1);
    in->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);
    */

	// set busy cursor
	Engine::Root::get_mutable_instance().GetResourceManagerPtr()->SetCursor(Engine::MOUSECURSOR_BUSY);
}

void IntroState::Update(float time_delta) {
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	if (resmgr->GetPercentageLoadingDone() < 1) {
		sf::Uint16 n = resmgr->LoadNextImage();
		sf::Uint16 m = resmgr->GetMaxImageQueueSize();
		mGuiSystems.begin()->GetControl<Engine::GuiProgressbar>("loading_progress")->SetProgress(resmgr->GetPercentageLoadingDone());
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("loading_progress_label")->SetText( "Loading images ... " +
			boost::lexical_cast<std::string>(n) +
			" / " +
			boost::lexical_cast<std::string>(m) );
	} else if(!mFinishedLoading) {
		mFinishedLoading = true;
		// pop current state (will not stop engine as it is popped at begin of next frame, when new states (see below) will be added).
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
		if(mShowMenu) {
			Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new MenuState());
		} else {
			Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PlayState());
		}
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("loading_progress_label")->SetText("Loading finished.");
		Engine::Root::get_mutable_instance().GetResourceManagerPtr()->SetCursor(Engine::MOUSECURSOR_ARROW);
	}
}

void IntroState::Shutdown() {}

void IntroState::OnCancel() {
    Engine::Root::get_mutable_instance().RequestShutdown();
}
void IntroState::OnClick(Engine::MouseEventArgs args) {
	// load playstate if finished loading
}
void IntroState::OnAnyKeyPressed() {
    // load playstate if finished loading
    //std::cout << "pressed" << std::endl;
}

void IntroState::SetShowMenu(bool show_menu) {
	mShowMenu = show_menu;
}
