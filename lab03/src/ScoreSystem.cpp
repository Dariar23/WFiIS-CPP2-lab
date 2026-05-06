#include "ScoreSystem.h"
#include <iostream>

void ScoreSystem::handleEvent(const Event& e) {
    switch (e.type) {
        case EventType::EnemyDied:
            std::cout << "[ScoreSystem] Enemy " 
                      << e.data.enemyDied.enemyId 
                      << " killed! +100 points\n";
            break;

        case EventType::EnemyDamaged:
            std::cout << "[ScoreSystem] Enemy " 
                      << e.data.enemyDamaged.enemyId 
                      << " took " << e.data.enemyDamaged.damage 
                      << " damage.\n";
            break;

        default:
            break;
    }
}
