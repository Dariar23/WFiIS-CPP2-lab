#include "LootSystem.h"
#include <iostream>

void LootSystem::handleEvent(const Event& e) {
    switch (e.type) {
        case EventType::EnemyDied:
            std::cout << "[LootSystem] Enemy "
                      << e.data.enemyDied.enemyId
                      << " dropped loot.\n";
            break;

        case EventType::ItemPicked:
            std::cout << "[LootSystem] Player "
                      << e.data.itemPicked.playerId
                      << " picked item: "
                      << e.data.itemPicked.itemName << "\n";
            break;

        default:
            break;
    }
}
