#include "Game.h"

#include "Constants.h"
#include "Math.h"
#include "RenderHelpers.h"

namespace ApplesGame
{
    bool Game::Init()
    {
        if (!m_resources.Load(k_ResourcesPath))
        {
            return false;
        }

        if (!m_audio.Init(k_ResourcesPath))
        {
            return false;
        }
        m_audio.PlayMusic();

        m_backgroundSprite.setTexture(m_resources.GetBackgroundTexture());
        FitSpriteToScreen(m_backgroundSprite, m_resources.GetBackgroundTexture());

        m_menuBackgroundSprite.setTexture(m_resources.GetMenuBackgroundTexture());
        FitSpriteToScreen(m_menuBackgroundSprite, m_resources.GetMenuBackgroundTexture());

        InitUI(m_ui, m_resources.GetUiFont(), m_resources.GetTitleFont());

        ResetGameplay();
        m_mode = EGameMode::MainMenu;
        m_ui.blinkTimerSeconds = 0.0F;

        return true;
    }

    void Game::Shutdown()
    {
        m_audio.Shutdown();
    }

    void Game::ResetGameplay()
    {
        m_player.Reset(m_resources.GetPlayerTexture());
        m_apple.Respawn(m_resources.GetAppleTexture());

        m_score = 0;

        UIModel model;
        model.score = m_score;
        model.mode = m_mode;
        UpdateUI(m_ui, model);
    }

    void Game::HandleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            if (m_mode == EGameMode::MainMenu || m_mode == EGameMode::GameOver)
            {
                ResetGameplay();
                m_mode = EGameMode::Playing;
            }
        }
    }

    void Game::OnAppleEaten()
    {
        m_score++;
        m_player.AddSpeed(k_Acceleration);

        m_audio.PlayEatApple();
        m_apple.Respawn(m_resources.GetAppleTexture());
    }

    void Game::UpdatePlaying(float dtSeconds)
    {
        m_player.HandleInput();
        m_player.Update(dtSeconds);

        if (m_player.HasCollisionWithScreenBorder())
        {
            m_mode = EGameMode::GameOver;
            m_ui.blinkTimerSeconds = 0.0F;
            return;
        }

        if (IsCirclesCollide(
            m_player.GetPosition(), m_player.GetRadius(),
            m_apple.GetPosition(), m_apple.GetRadius()))
        {
            OnAppleEaten();
        }
    }

    void Game::Update(float dtSeconds)
    {
        switch (m_mode)
        {
        case EGameMode::MainMenu:
            UpdateMenuUI(m_ui, dtSeconds);
            break;

        case EGameMode::Playing:
            UpdatePlaying(dtSeconds);
            break;

        case EGameMode::GameOver:
            UpdateGameOverUI(m_ui, dtSeconds);
            break;
        }

        UIModel model;
        model.score = m_score;
        model.mode = m_mode;
        UpdateUI(m_ui, model);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        if (m_mode == EGameMode::MainMenu)
        {
            DrawMenuUI(m_ui, window, m_menuBackgroundSprite);
            return;
        }

        // 1) Background
        window.draw(m_backgroundSprite);

        // 2) World
        m_player.Draw(window);
        m_apple.Draw(window);

        // 3) UI over world
        DrawUI(m_ui, window);

        // 4) Overlay
        if (m_mode == EGameMode::GameOver)
        {
            DrawGameOverOverlay(m_ui, window);
        }
    }
}
