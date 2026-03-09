// @file Game.h

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "AudioManager.h"
#include "Apple.h"
#include "GameMode.h"
#include "GameRules.h"
#include "Player.h"
#include "Resources.h"
#include "UI.h"

namespace ApplesGame
{
    struct MenuSprites
    {
        sf::Sprite main;
        sf::Sprite choose;
    };

    struct LeaderboardEntry
    {
        std::string name;
        int score = 0;
        bool isPlayer = false;
    };

    class Game
    {
    public:
        bool Init();
        void Shutdown();

        void HandleEvent(const sf::Event& event);
        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        bool ShouldExit() const
        {
            return m_RequestExit;
        }

    private:
        // Core
        void ResetGameplay();
        void UpdatePlaying(float dtSeconds);
        void EnterGameOver();

        // Apples
        void AllocateApples(int count);
        void FreeApples();
        void OnAppleEaten(int index);

        // Rules
        void EnsureDefaultRules();
        int GetInitialAppleCountFromRules() const;
        bool IsInfiniteMode() const;
        void ApplyChooseSelection();

        // Leaderboard
        void GenerateLeaderboard();
        void UpdatePlayerLeaderboard();
        void SortLeaderboardDescending();

        // Input
        void HandleMainMenuInput(sf::Keyboard::Key key);
        void HandleChooseModeInput(sf::Keyboard::Key key);
        void HandleGameOverInput(sf::Keyboard::Key key);
        void HandleLeaderboardInput(sf::Keyboard::Key key);

    private:
        static const int k_MainMenuCount = 2;
        static const int k_ChooseMenuCount = 6;
        static const int k_GameOverCount = 3;
        static const int k_ChooseStartIndex = 5;
        static const int k_LeaderboardCount = 7;

    private:
        EGameMode m_Mode = EGameMode::MainMenu;
        bool m_RequestExit = false;

        int m_MainMenuIndex = 0;
        int m_ChooseIndex = k_ChooseStartIndex;
        int m_GameOverIndex = 0;

        EGameRule m_Rules = EGameRule::None;
        int m_Score = 0;

        Player m_Player;

        Apple* m_Apples = nullptr;
        int m_ApplesCount = 0;

        LeaderboardEntry m_Leaderboard[k_LeaderboardCount];

        Resources m_Resources;
        AudioManager m_Audio;
        UIState m_Ui;

        sf::Sprite m_Background;
        MenuSprites m_MenuSprites;
    };
}