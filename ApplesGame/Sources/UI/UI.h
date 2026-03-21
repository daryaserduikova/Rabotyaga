#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

#include "GameMode.h"
#include "GameRules.h"

namespace ApplesGame
{
    constexpr int k_MaxLeaderboardEntries = 7;

    // UI MODEL
    struct UIModel
    {
        EGameMode mode = EGameMode::MainMenu;
        int score = 0;

        int mainMenuIndex = 0;
        int chooseIndex = 0;
        int gameOverIndex = 0;

        EGameRule rules = EGameRule::None;

        int leaderboardCount = 0;
        std::array<std::string, k_MaxLeaderboardEntries> leaderboardNames{};
        std::array<int, k_MaxLeaderboardEntries> leaderboardScores{};
    };

    struct UIState
    {
        // MAIN
        sf::Text mainTitleText;
        sf::Text playText;
        sf::Text exitText;

        // CHOOSE
        sf::Text chooseTitleText;
        sf::Text chooseApplesHeaderText;
        sf::Text chooseFinite20Text;
        sf::Text chooseFinite50Text;
        sf::Text chooseInfiniteText;
        sf::Text chooseSpeedHeaderText;
        sf::Text chooseSpeedUpText;
        sf::Text chooseNoSpeedUpText;
        sf::Text chooseStartText;

        // HUD
        sf::Text scoreText;

        // GAME OVER
        sf::Text gameOverTitleText;
        sf::Text gameOverMenuText;

        // LEADERBOARD
        sf::Text leaderboardTitleText;
        sf::Text leaderboardEntryTexts[k_MaxLeaderboardEntries];
        sf::Text leaderboardScoreTexts[k_MaxLeaderboardEntries];
        sf::Text leaderboardBackText;
    };

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont);
    void UpdateUI(UIState& ui, const UIModel& model);

    void DrawMainMenu(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background);
    void DrawChooseMode(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background);
    void DrawHud(UIState& ui, sf::RenderWindow& window);
    void DrawGameOver(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background);
    void DrawLeaderboard(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background);
}