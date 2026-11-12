#pragma once
#include <string>
enum AI{
    NEUTRAL,
    ALLY,
    ENEMY
};
inline std::string aiToString(AI ai) {
    switch (ai) {
        case AI::NEUTRAL: return "Neutral";
        case AI::ALLY:    return "Ally";
        case AI::ENEMY:   return "Enemy";
        default:          return "Unknown";
    }
}