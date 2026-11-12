#pragma once

#include <iostream> 
enum Faction{
    NEW_CAMP,
    OLD_CAMP,
    NONE
};
inline std::string factionToString(Faction f) {
    switch (f) {
        case Faction::NEW_CAMP: return "New Camp";
        case Faction::OLD_CAMP: return "Old Camp";
        case Faction::NONE: return "None";
        default: return "Unknown";  
    }
}

