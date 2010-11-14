#include "LoadingState.hpp"

#include "Root.hpp"

LoadingState::LoadingState() {}
LoadingState::~LoadingState() {}

// state control
void LoadingState::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing LoadingState.");

	// load resources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	// GUI
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button.svg", 0.048f, 0.048f, "gui.button");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_hover.svg",	0.048f,	0.048f,	"gui.button_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_focus.svg", 0.048f, 0.048f,	"gui.button_focus");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"grid.svg", 0.048f, 0.048f, "gui.grid");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox.svg", 0.016f, 0.016f, "gui.checkbox");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox_checked.svg", 0.016f, 0.016f, "gui.checkbox_checked");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"checkbox_hover.svg", 0.016f, 0.016f, "gui.checkbox_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"textfield2.svg", 0.024f, 0.024f, "gui.textfield");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"progressbar_back.svg", 0.024f, 0.024f, "gui.progressbar_back");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"progressbar_front.svg", 0.024f, 0.024f, "gui.progressbar_front");

	// IMAGES
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"submarine1.svg", 0.08f, 0.053f, "submarine");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"submarine_target.svg", 0.02f,	0.02f,	"submarine_target");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"sonarping.svg", 0.02f, 0.02f, "sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"torpedo1.svg", 0.03f, 0.01f, "torpedo");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"missing.svg", 0.08f, 0.053f, "missing");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle1.svg", 0.024f, 0.024f, "particle1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_cursor.svg", 0.024f,	0.024f, "particle_cursor");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_bubble.svg", 0.024f, 0.024f, "particle_bubble");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"particle_sonarping.svg", 0.04f, 0.04f, "particle_sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"glow1.svg", 0.05f, 0.05f, "glow1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),
			"torpedo_trail.svg", 0.024f, 0.024f, "torpedo_trail");

	resmgr->LoadAllQueuedImagesInBackground();

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
	l->SetFontColor(sf::Color::White);
	l->SetFontSize(11);
	mGuiSystems.begin()->AddControl(l);


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

void LoadingState::Update(float time_delta) {
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();
	Engine::LoadingStatus ls = resmgr->GetLoadingStatus();
	// std::cout << "Loading ... " << ceil(ls.GetPercentage() * 100) << std::endl;
	if (ls.GetPercentage() >= 1) {
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PlayState());
	} else {
		mGuiSystems.begin()->GetControl<Engine::GuiProgressbar>("loading_progress")->SetProgress(ls.GetPercentage());
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("loading_progress_label")->SetText( "Loading images ... " +
			boost::lexical_cast<std::string>(ls.GetImagesLoaded()) + " / " + boost::lexical_cast<std::string>(ls.GetTotalImages()));
	}
}

void LoadingState::Shutdown() {}

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
