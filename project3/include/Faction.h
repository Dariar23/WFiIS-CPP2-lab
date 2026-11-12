#pragma once
#include <iostream>

enum Faction{
    NEW_CAMP,
    OLD_CAMP,
    NONE
};
std::string factionToString( Faction frac){
    switch(frac){
        case Faction::NEW_CAMP: return "New Camp";
        case Faction::OLD_CAMP: return "Old Camp";
        case Faction::NONE: return "None";
        default:
            return "" ;
    }
}