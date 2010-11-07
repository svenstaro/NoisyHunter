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
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"button.svg",				48,		48,		"gui.button");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"button_hover.svg",		48,		48,		"gui.button_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"button_focus.svg",		48,		48,		"gui.button_focus");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"grid.svg",		48,		48,		"gui.grid");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"checkbox.svg",			16,		16,		"gui.checkbox");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"checkbox_checked.svg",	16,		16,		"gui.checkbox_checked");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"checkbox_hover.svg",		16,		16,		"gui.checkbox_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"textfield2.svg",			24,		24,		"gui.textfield");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"progressbar_back.svg",	24,		24,		"gui.progressbar_back");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),"progressbar_front.svg",	24,		24,		"gui.progressbar_front");

	// IMAGES
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"submarine1.svg",			80,		53,		"submarine");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"sonarping.svg",			20,		20,		"sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"torpedo1.svg",			30,		10,		"torpedo");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"missing.svg",			80,		53,		"missing");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"particle1.svg",			24,		24,		"particle1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"particle_cursor.svg",	24,		24,		"particle_cursor");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"particle_bubble.svg",	24,		24,		"particle_bubble");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"particle_sonarping.svg",	20,		20,		"particle_sonarping");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"glow1.svg",				50,		50,	"glow1");
	resmgr->AddImageToLoadingQueue(boost::filesystem::path("../game/gfx"),"torpedo_trail.svg",		24,		24,		"torpedo_trail");

    // load font
    sf::Font font;
    font.LoadFromFile("../game/fonts/kingthings_trypewriter_2.ttf");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddFont(font, "default");
    font.LoadFromFile("../game/fonts/ParmaPetit-Normal.ttf");
    Engine::Root::get_mutable_instance().GetResourceManagerPtr()->AddFont(font, "serif");

    // create gui
    CreateGuiSystem();

	Engine::GuiProgressbar* p = new Engine::GuiProgressbar("loading_progress");
	p->SetPosition(Engine::Vector2D(300,280));
	p->SetDimension(Engine::Vector2D(200,40));
	mGuiSystems.begin()->AddControl(p);

	Engine::GuiLabel* l = new Engine::GuiLabel("loading_progress_label");
	l->SetPosition(300,330);
	l->SetText("Loading images...");
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
	sf::Sleep(0.1);
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	if (resmgr->GetPercentageLoadingDone() >= 1) {
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new PlayState());
	} else {
		sf::Uint16 n = resmgr->LoadNextImage();
		sf::Uint16 m = resmgr->GetMaxImageQueueSize();
		mGuiSystems.begin()->GetControl<Engine::GuiProgressbar>("loading_progress")->SetProgress(resmgr->GetPercentageLoadingDone());
		mGuiSystems.begin()->GetControl<Engine::GuiLabel>("loading_progress_label")->SetText( "Loading images ... " +
			boost::lexical_cast<std::string>(n) +
			" / " +
			boost::lexical_cast<std::string>(m) );
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
