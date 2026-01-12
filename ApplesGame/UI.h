#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace ApplesGame
{
    struct Resources;

    struct UIState
    {
        // HUD
        sf::Text scoreText;
        int lastScore = -1;

        // Screens (Menu/GameOver)
        sf::Text menuTitleText;
        sf::Text menuContinueText;

        sf::Text gameOverText;
        sf::Text restartText;

        // UI animation state
        float blinkTimerSeconds = 0.0F;
    };

    void InitUI(UIState& ui, const Resources& resources);

    void UpdateUI(UIState& ui, const GameState& state);
    void DrawUI(UIState& ui, sf::RenderWindow& window);

    // Screen UI (Menu/GameOver)
    void UpdateMenuUI(UIState& ui, float deltaTimeSeconds);
    void DrawMenuUI(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground);

    void UpdateGameOverUI(UIState& ui, float deltaTimeSeconds);
    void DrawGameOverOverlay(UIState& ui, sf::RenderWindow& window);

    // Helpers
    void SetupCenteredText(sf::Text& text, float x, float y);
}
