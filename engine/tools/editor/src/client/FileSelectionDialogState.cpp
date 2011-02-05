#include "FileSelectionDialogState.hpp"

#include "Root.hpp"

FileSelectionDialogState::FileSelectionDialogState() {}

FileSelectionDialogState::~FileSelectionDialogState() {}

void FileSelectionDialogState::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing FileSelectionDialogState.");

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
	resmgr->AddImage(boost::filesystem::path("../game/gui"),
			"textfield2.svg", 0.24f, 0.24f, "gui.textfield");


	// Gui grid for buttons
	Engine::GuiGrid* grid = new Engine::GuiGrid("debug_grid");
	grid->SetDimension(Engine::Vector2D(160, 100));
	Engine::Vector2D size(Engine::Root::get_mutable_instance().GetWindowSize());
	size -= grid->GetDimension();
	size /= 2;
	grid->SetPosition(size.x, size.y);

	// Resume button
	Engine::GuiButton* b;

	Engine::GuiTextfield* t;

	t = new Engine::GuiTextfield("filename_input");
	grid->AddControl(t);

	Engine::GuiGrid* btn_grid = new Engine::GuiGrid("btn_grid");
	btn_grid->SetDimension(Engine::Vector2D(160, 25));
	btn_grid->SetColumns(2);

	b = new Engine::GuiButton("resume_button");
	b->SetText("Ok");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&FileSelectionDialogState::OkButton_OnClick, this, _1));
	btn_grid->AddControl(b);

	b = new Engine::GuiButton("exit_button");
	b->SetText("Cancel");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&FileSelectionDialogState::ExitButton_OnClick, this, _1));
	btn_grid->AddControl(b);

	grid->AddControl(btn_grid);

	mGuiSystems.begin()->AddControl(grid);

	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	// Bind Keys
	Engine::KeyBindingCallback cb = boost::bind(&FileSelectionDialogState::OnPressEscape, this);
	inputmgr->BindKey( cb, Engine::KEY_PRESSED, sf::Key::Escape );
}

void FileSelectionDialogState::Shutdown() {
	Engine::Logger::Message(Engine::LogOrigin::STATE, "Closed FileSelectionDialogState.");
}

void FileSelectionDialogState::Update(float time_delta) {
	UpdateAllEntities(time_delta);
}

void FileSelectionDialogState::Draw(sf::RenderTarget* target) {
	target->Draw(mBackgroundShape);
}

bool FileSelectionDialogState::StatesBelowArePaused() {
	return false;
}

bool FileSelectionDialogState::StatesBelowAreHidden() {
	return false;
}

void FileSelectionDialogState::OkButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
	std::string text = mGuiSystems.back().GetControl<Engine::GuiTextfield>("filename_input")->GetText();
	mWorlds.back().SaveWorld(text);
}

void FileSelectionDialogState::ExitButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}

void FileSelectionDialogState::OnPressEscape() {
	if(IsCurrentState())
		// TODO: sometimes this is called twice ;( fix those events
		Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}
