#include "SoundSystem.h"
#include <iostream>

void SoundSystem::handleEvent(const Event& e) {
    switch (e.type) {
    case EventType::EnemyDamaged: {
        std::cout << "[SoundSystem] Play hit sound.\n";
        break;
    }
    case EventType::EnemyDied: {
        std::cout << "[SoundSystem] Play death sound.\n";
        break;
    }
    case EventType::PlayerHealed: {
        std::cout << "[SoundSystem] Play heal sound.\n";
        break;
    }
    case EventType::ItemPicked: {
        std::cout << "[SoundSystem] Play pickup sound.\n";
        break;
    }
    }
}
