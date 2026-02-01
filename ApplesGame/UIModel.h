#pragma once
#include "GameMode.h"
#include "GameRules.h"

namespace ApplesGame
{
    struct UIModel
    {
        EGameMode mode = EGameMode::Splash;
        int score = 0;

        int mainMenuIndex = 0;
        int chooseIndex = 5;
        int gameOverIndex = 0;

        EGameRule rules = EGameRule::None;
    };
}
