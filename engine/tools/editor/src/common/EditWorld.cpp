#include <iostream>

#include "EditWorld.hpp"
#include "Root.hpp"

EditWorld::EditWorld() {}
EditWorld::~EditWorld() {}
EditWorld* EditWorld::clone() const {
	return new EditWorld();
}

// state control
void EditWorld::Initialize() {
	Engine::Logger::Urgent(Engine::LogOrigin::STATE, "Initializing EditWorld.");
	// only bind events in client mode
	if (! Engine::Root::get_mutable_instance().IsServer()) {
		auto inputmgr = Engine::Root::get_mutable_instance().GetInputManagerPtr();
		// bind mouse
		Engine::MouseBindingCallback mcb = boost::bind(&EditWorld::OnClick, this, _1);
		inputmgr->BindMouse(mcb, Engine::BUTTON_PRESSED, sf::Mouse::Left);
		Engine::MouseBindingCallback right = boost::bind(&EditWorld::OnRightClick, this, _1);
		inputmgr->BindMouse(right, Engine::BUTTON_PRESSED, sf::Mouse::Right);

		// mouse cursor
		Engine::MouseBindingCallback mv = boost::bind(&EditWorld::OnMouseMove, this, _1);
		inputmgr->BindMouse(mv, Engine::MOUSE_MOVED);
	}
}

void EditWorld::Update(const float time_delta) {
	UpdateAllEntities(time_delta);
}

void EditWorld::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {
	sf::Int16 x,y;
	data >> x >> y;

	if(interaction_id == CREATE_TILE) {
		bool ok = true;

		BOOST_FOREACH(Engine::Entity& e, mEntities) {
			if(e.GetEntityTypeId() == ENTITYTYPEID_TILE) {
				if(floor(e.GetPosition().x) == x && floor(e.GetPosition().y) == y )
					ok = false;
			}
		}

		if(ok) {
			Tile* t = new Tile();
			t->Initialize("tileset", x, y);
			AddEntity(t);
		}
	} else if(interaction_id == REMOVE_TILE) {
		BOOST_FOREACH(Engine::Entity& e, mEntities) {
			if(e.GetEntityTypeId() == ENTITYTYPEID_TILE) {
				if(floor(e.GetPosition().x) == x && floor(e.GetPosition().y) == y ) {
					Engine::Root::get_mutable_instance().GetNetworkManagerPtr()->SendEntityDel(e.GetEntityUniqueId(), mWorldUniqueId);
					DeleteEntityByEntityUniqueId(e.GetEntityUniqueId());
				}
			}
		}
	} else if(interaction_id == FILE_OPEN) {

	} else if(interaction_id == FILE_SAVE) {
		std::string f;
		data >> f;
		bool success = SaveWorld(f);

		Engine::NetworkManager* netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
		sf::Packet packet;
		packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(SAVE_RESULT);
		packet << success;
		netmgr->SendPacket(packet);
	} else if(interaction_id == SAVE_RESULT) {
		bool success;
		data >> success;

		std::string msg = "Successful.";
		if(!success)
			msg = "Fail!!! :P";

		Engine::Logger::Critical(Engine::LogOrigin::WORLD, msg);
	}
}

void EditWorld::OnClick(Engine::MouseEventArgs args) {
	sf::Int16 x = floor(args.GetWorldFloat().x);
	sf::Int16 y = floor(args.GetWorldFloat().y);

	Engine::NetworkManager* netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(CREATE_TILE);
	packet << GetWorldUniqueId();
	packet << x << y;
	netmgr->SendPacket(packet);
}
void EditWorld::OnRightClick(Engine::MouseEventArgs args) {
	sf::Int16 x = floor(args.GetWorldFloat().x);
	sf::Int16 y = floor(args.GetWorldFloat().y);

	Engine::NetworkManager* netmgr = Engine::Root::get_mutable_instance().GetNetworkManagerPtr();
	sf::Packet packet;
	packet << sf::Uint16(Engine::NETCMD_INTERACTION) << sf::Uint16(REMOVE_TILE);
	packet << GetWorldUniqueId();
	packet << x << y;
	netmgr->SendPacket(packet);
}
void EditWorld::OnMouseMove(Engine::MouseEventArgs args) {}

sf::Uint16 EditWorld::GetWorldTypeId() const {
	return WORLDTYPEID_EDITWORLD;
}
