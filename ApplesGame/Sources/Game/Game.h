// @file Game.h

#pragma once
#include <SFML/Graphics.hpp>

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

    class Game
    {
    public:
        bool Init();

        void HandleEvent(const sf::Event& event);

        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        void Shutdown();

        bool ShouldExit() const
        {
            return m_RequestExit;
        }

    private:
        void ResetGameplay();
        void UpdatePlaying(float dtSeconds);

        void AllocateApples(int count);
        void FreeApples();

        void OnAppleEaten(int appleIndex);

        bool IsInfiniteApplesMode() const;
        int GetInitialAppleCountFromRules() const;

        void EnsureDefaultRules();

        void ApplyChooseSelection();
        void StartFromChooseMode();

    private:
        EGameMode m_Mode = EGameMode::Splash;
        bool m_RequestExit = false;

        int m_MainMenuIndex = 0;
        int m_ChooseIndex = 5;
        int m_GameOverIndex = 0;

        float m_SplashTimerSeconds = 0.0F;

        EGameRule m_Rules = EGameRule::None;

        int m_Score = 0;
        Player m_Player;

        Apple* m_Apples = nullptr;
        int m_ApplesCount = 0;

        Resources m_Resources;
        UIState m_Ui;
        AudioManager m_Audio;

        sf::Sprite m_BackgroundSprite;
        MenuSprites m_MenuSprites;
        sf::Sprite m_SplashSprite;
    };
}