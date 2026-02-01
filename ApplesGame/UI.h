#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>

#include "UIModel.h"

namespace ApplesGame
{
    struct UIState
    {
        // HUD
        sf::Text scoreText;
        int lastScore = -1;

        // Splash
        sf::Text splashTitleText;
        sf::Text splashHintText;

        // Main menu
        sf::Text mainTitleText;
        sf::Text playText;
        sf::Text exitText;

        // Choose mode
        sf::Text chooseTitleText;
        sf::Text chooseListText;

        // Game over
        sf::Text gameOverTitleText;
        sf::Text gameOverListText;
    };

    void SetupCenteredText(sf::Text& text, float x, float y);

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont);
    void UpdateUI(UIState& ui, const UIModel& model);

    void DrawSplash(
        UIState& ui,
        sf::RenderWindow& window,
        const sf::Sprite& splashSprite,
        std::uint8_t alpha,
        float timeSeconds);

    void DrawMainMenu(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground);
    void DrawChooseMode(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground);

    void DrawHud(UIState& ui, sf::RenderWindow& window);
    void DrawGameOver(UIState& ui, sf::RenderWindow& window);
}
