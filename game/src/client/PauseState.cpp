#include "PauseState.hpp"

#include "Root.hpp"

PauseState::PauseState() {}

PauseState::~PauseState() {}

void PauseState::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing PauseState.");

	mBackgroundShape = sf::Shape::Rectangle(0,0,800,600,sf::Color(0,0,0,128));

	CreateGuiSystem();

	// Resume button
	Engine::GuiButton* b;

	b = new Engine::GuiButton("resume_button");
	b->SetDimension(Engine::Vector2D(300,50));
	b->SetPosition(Engine::Vector2D(250,240));
	b->SetText("Resume Game");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::ResumeButton_OnClick, this, _1));
	mGuiSystems.begin()->AddControl(b);

	b = new Engine::GuiButton("exit_button");
	b->SetDimension(Engine::Vector2D(300,50));
	b->SetPosition(Engine::Vector2D(250,300));
	b->SetText("Quit to Title");
	b->SetFont(sf::Font::GetDefaultFont());
	b->SetFontSize(13);
	b->SetFontStyle(sf::Text::Regular);
	b->SetFontColor(sf::Color::White);
	b->BindOnClick(boost::bind(&PauseState::ExitButton_OnClick, this, _1));
	mGuiSystems.begin()->AddControl(b);

}

void PauseState::Shutdown() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Closed PauseState.");
}

void PauseState::Update(float time_delta) {
	UpdateAllEntities(time_delta);
}

void PauseState::Draw(sf::RenderTarget* target) {
	target->Draw(mBackgroundShape);
}

bool PauseState::StatesBelowArePaused() {
	return false;
}

bool PauseState::StatesBelowAreHidden() {
	return false;
}

void PauseState::ResumeButton_OnClick(const sf::Uint16 mouse_button) {
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->Pop();
}

void PauseState::ExitButton_OnClick(const sf::Uint16 mouse_button) {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Quitting game.");
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_NETWORK, "Sending packet with NETCMD_CLIENTQUIT.");

	// Send NETCMD_CLIENTQUIT to server
	auto netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	netmgr->SendClientQuit();

	Engine::Root::get_mutable_instance().RequestShutdown();
}
