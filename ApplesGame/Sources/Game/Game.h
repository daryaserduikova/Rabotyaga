//@file Game.h

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "AudioManager.h"
#include "Apple.h"
#include "GameMode.h"
#include "GameRules.h"
#include "Player.h"
#include "Resources.h"
#include "UI.h"
#include "Leaderboard.h"

namespace ApplesGame
{
    struct MenuSprites
    {
        sf::Sprite main;
        sf::Sprite choose;
    };

    class Game
    {
    public:
        bool Init();
        void Shutdown();

        void HandleEvent(const sf::Event& event);
        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        bool ShouldExit() const { return m_RequestExit; }

    private:
        void ResetGameplay();
        void UpdatePlaying(float dtSeconds);
        void EnterGameOver();
        void EnterVictory();

    private:
        static const int k_MainMenuCount = 3;
        static const int k_ChooseMenuCount = 6;
        static const int k_GameOverCount = 2;
        static const int k_PauseMenuCount = 2;

    private:
        EGameMode m_Mode = EGameMode::MainMenu;
        bool m_RequestExit = false;

        int m_MainMenuIndex = 0;
        int m_ChooseIndex = 5;
        int m_GameOverIndex = 0;
        int m_PauseIndex = 0;

        EGameRule m_Rules = EGameRule::None;
        int m_Score = 0;

        Player m_Player;
        std::vector<Apple> m_Apples;

        std::unique_ptr<Leaderboard> m_Leaderboard;
        std::unique_ptr<Resources> m_Resources;
        std::unique_ptr<AudioManager> m_Audio;
        std::unique_ptr<UIState> m_Ui;

        UIModel m_UiModel;

        sf::Sprite m_Background;
        MenuSprites m_MenuSprites;
    };
}