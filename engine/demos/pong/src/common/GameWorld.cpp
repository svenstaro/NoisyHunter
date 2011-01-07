#include "GameWorld.hpp"

GameWorld::GameWorld() {}
GameWorld::~GameWorld() {}
GameWorld* GameWorld::clone() const {
    return new GameWorld();
}

void GameWorld::Initialize() {}

void GameWorld::Update(float time_diff) {
    UpdateAllEntities(time_diff);
}
void GameWorld::HandleInteraction(const sf::Uint16 interaction_id, const sf::Uint16 client_id, sf::Packet& data) {
    if(interaction_id == 0x01) { // move up

    } else if(interaction_id == 0x02) { // move down

    }
}

void GameWorld::OnPressUp() {}
void GameWorld::OnPressDown() {}

sf::Uint16 GameWorld::GetWorldTypeId() const {
    return 0x0102;
}
