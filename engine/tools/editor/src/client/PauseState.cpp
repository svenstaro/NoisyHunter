#include "PauseState.hpp"
#include "FileSelectionDialogState.hpp"

#include "Root.hpp"

PauseState::PauseState() {}

PauseState::~PauseState() {}

void PauseState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing PauseState.");

	mBackgroundShape = sf::Shape::Rectangle(0,0,800,600,sf::Color(0,0,0,128));

	CreateGuiSystem();

	// Load Resources
	auto resmgr = Engine::Root::get_mutable_instance().GetResourceManagerPtr();

	// GUI
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button.svg", 0.48f, 0.48f, "gui.button");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_hover.svg",	0.48f,	0.48f,	"gui.button_hover");
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"button_focus.svg", 0.48f, 0.48f,	"gui.button_focus");


	// Gui grid for buttons
	Engine::GuiGrid* grid = new Engine::GuiGrid("debug_grid");
	grid->SetDimension(Engine::Vector2D(160, 160));
	Engine::Vector2D size(Engine::Root::get_mutable_instance().GetWindowSize());
	size -= grid->GetDimension();
	size /= 2;
	grid->SetPosition(size.x, size.y);

	// Resume button
	Engine::GuiButton* b;

	b = new Engine::GuiButton("resume_button");
	b->SetText("Resume Editor");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::ResumeButton_OnClick, this, _1));
	grid->AddControl(b);

	b = new Engine::GuiButton("file_open_button");
	b->SetText("Open Map");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::FileOpenButton_OnClick, this, _1));
	grid->AddControl(b);

	b = new Engine::GuiButton("file_save_button");
	b->SetText("Save Map");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::FileSaveButton_OnClick, this, _1));
	grid->AddControl(b);

	b = new Engine::GuiButton("file_save_as_button");
	b->SetText("Save Map As");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::FileSaveAsButton_OnClick, this, _1));
	grid->AddControl(b);

	b = new Engine::GuiButton("exit_button");
	b->SetText("Quit");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::ExitButton_OnClick, this, _1));
	grid->AddControl(b);

	mGuiSystems.begin()->AddControl(grid);

	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	// Bind Keys
	Engine::KeyBindingCallback cb = boost::bind(&PauseState::OnPressEscape, this);
	inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
}

void PauseState::Shutdown() {
	Engine::Logger::Message(Engine::LogOrigin::STATE, "Closed PauseState.");
}

void PauseState::Update(float time_delta) {
	UpdateAllEntities(time_delta);
}

void PauseState::Draw(sf::RenderTarget* target) {
	target->Draw(mBackgroundShape);
}

bool PauseState::StatesBelowArePaused() {
	return true;
}

bool PauseState::StatesBelowAreHidden() {
	return false;
}

void PauseState::ResumeButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}

void PauseState::FileOpenButton_OnClick(const sf::Uint16 mouse_button) {
	//Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Add(new FileSelectionDialogState());
}

void PauseState::FileSaveButton_OnClick(const sf::Uint16 mouse_button) {
	//Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}

void PauseState::FileSaveAsButton_OnClick(const sf::Uint16 mouse_button) {
	//Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}

void PauseState::ExitButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop(2);
}

void PauseState::OnPressEscape() {
	if(IsCurrentState())
		// TODO: sometimes this is called twice ;( fix those events
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}
