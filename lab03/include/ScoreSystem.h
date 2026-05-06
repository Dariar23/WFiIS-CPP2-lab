#pragma once
#include "EventBus.h"

class ScoreSystem {
public:
    static void handleEvent(const Event& e);
};
