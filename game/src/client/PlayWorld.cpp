#include <iostream>

#include "PlayWorld.hpp"
#include "Root.hpp"

PlayWorld::PlayWorld() {}

PlayWorld::~PlayWorld() {}

void PlayWorld::Initialize() {
	auto logmgr = Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_URGENT, Engine::LOGORIGIN_STATE, "Initializing PlayWorld.");

	auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
	// bind keys
	Engine::KeyBindingCallback cb2 = boost::bind(&PlayWorld::TriggerFireSonarPing, this);
	inputmgr->BindKey( cb2, Engine::KEY_PRESSED, sf::Key::Space );
	// bind mouse
	Engine::MouseBindingCallback mcb = boost::bind(&PlayWorld::OnClick, this, _1);
	inputmgr->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
	Engine::MouseBindingCallback right = boost::bind(&PlayWorld::OnRightClick, this, _1);
	inputmgr->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

	// mouse cursor
	Engine::MouseBindingCallback mv = boost::bind(&PlayWorld::OnMouseMove, this, _1);
	inputmgr->BindMouse(mv, Engine::MOUSE_MOVED);
	// hide original cursor
	Engine::Root::get_mutable_instance().SetMouseHidden(true);
}

void PlayWorld::Update(float time_delta) {
    UpdateAllEntities(time_delta);

	BOOST_FOREACH(Submarine* sub, GetAllEntitiesByType<Submarine>()) {
		if (sub->GetClientId() == Engine::Root::get_mutable_instance().GetClientId()) {
			Engine::Root::get_mutable_instance().CenterViewAt(Engine::Coordinates::WorldFloatToWorldPixel(sub->GetPosition()));
		}
	}

	if (Engine::Root::get_mutable_instance().GetInputManagerPtr()->IsMouseButtonDown(sf::Mouse::Left)) {
		// Send submarine to mouse position
		Engine::Coordinates c;
		c.SetScreenPixel(Engine::Root::get_mutable_instance().GetMousePosition());
		OnNavigateTo(c);
	}
}

void PlayWorld::OnSetNoisyMode() {
//	if(IsCurrentState())
		//mPlayerSubmarine->SetMode(Submarine::MODE_NOISY);
}
void PlayWorld::OnSetSilentMode() {
//	if(IsCurrentState())
		//mPlayerSubmarine->SetMode(Submarine::MODE_SILENT);
}

void PlayWorld::OnNavigateTo(const Engine::Coordinates& mouse_position) {	
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_SETSUBMARINETARGET);
	packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
}

void PlayWorld::OnFireTorpedo(const Engine::Coordinates& mouse_position) {
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_FIRETORPEDO);
	packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
	packet << 3.f; // time_to_live
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
}

void PlayWorld::OnFireSonarPing(const Engine::Coordinates& mouse_position) {
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(INTERACTION_FIRESONARPING);
	packet << mouse_position.GetWorldFloat().x << mouse_position.GetWorldFloat().y;
	packet << 5.f;
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendPacket(packet);
}

void PlayWorld::TriggerFireSonarPing() {
	Engine::Coordinates c;
	c.SetScreenPixel(Engine::Root::get_mutable_instance().GetMousePosition());
	OnFireSonarPing(c);
}

void PlayWorld::OnClick(Engine::MouseEventArgs args) {
	OnNavigateTo(args);
	Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendChatMessage("I am so glad I just clicked!");
}

void PlayWorld::OnRightClick(Engine::MouseEventArgs args) {
	OnFireTorpedo(args);
}

void PlayWorld::OnMouseMove(Engine::MouseEventArgs args) {
	//mCursorPartSys->SetPosition(args.GetScreenPixel().x, args.GetScreenPixel().y);
}
