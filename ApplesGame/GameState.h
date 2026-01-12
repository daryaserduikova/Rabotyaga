#pragma once
#include "Player.h"
#include "Apple.h"

namespace ApplesGame
{
    enum class EGameMode
    {
        MainMenu = 0,
        Playing,
        GameOver
    };

    struct GameState
    {
        Player player;
        Apple apple;

        int score = 0;
        EGameMode mode = EGameMode::MainMenu;

        // For UI
        float blinkTimerSeconds = 0.0F;
    };
}
