#pragma once
#include <SFML/Graphics.hpp>

#include "AudioManager.h"
#include "Apple.h"
#include "GameMode.h"
#include "Player.h"
#include "Resources.h"
#include "UI.h"

namespace ApplesGame
{
    class Game
    {
    public:
        bool Init();

        // ќбработка только игровых событий (перезапуск на SPACE)
        void HandleEvent(const sf::Event& event);

        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        void Shutdown();

    private:
        void ResetGameplay();
        void UpdatePlaying(float dtSeconds);
        void OnAppleEaten();

    private:
        EGameMode m_mode = EGameMode::MainMenu;
        int m_score = 0;

        Player m_player;
        Apple m_apple;

        Resources m_resources;
        UIState m_ui;
        AudioManager m_audio;

        sf::Sprite m_backgroundSprite;
        sf::Sprite m_menuBackgroundSprite;
    };
}
