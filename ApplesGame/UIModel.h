#pragma once
#include "GameMode.h"

namespace ApplesGame
{
    struct UIModel
    {
        int score = 0;
        EGameMode mode = EGameMode::MainMenu;
    };
}
