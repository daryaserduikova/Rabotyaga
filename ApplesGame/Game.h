#pragma once
#include <SFML/Graphics.hpp>

#include "AudioManager.h"
#include "GameState.h"
#include "Resources.h"
#include "UI.h"

namespace ApplesGame
{
    struct Game
    {
        GameState state;

        Resources resources;
        UIState ui;

        sf::Sprite backgroundSprite;
        sf::Sprite menuBackgroundSprite;

        AudioManager audio;
    };

    bool InitGame(Game& game);
    void ResetGameplay(Game& game);
    void HandleInput(Game& game);
    void UpdateGame(Game& game, float deltaTimeSeconds);
    void DrawGame(Game& game, sf::RenderWindow& window);
}
