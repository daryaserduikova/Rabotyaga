#include "Game.h"

#include "Constants.h"
#include "Math.h"
#include "RenderHelpers.h"

namespace ApplesGame
{
    bool Game::Init()
    {
        if (!m_resources.Load(Paths::Resources))
        {
            return false;
        }

        if (!m_audio.Init(Paths::Resources))
        {
            return false;
        }
        m_audio.PlayMusic();

        m_backgroundSprite.setTexture(m_resources.BackgroundTexture());
        FitSpriteToScreen(m_backgroundSprite, m_resources.BackgroundTexture());

        m_menuBackgroundSprite.setTexture(m_resources.MenuBackgroundTexture());
        FitSpriteToScreen(m_menuBackgroundSprite, m_resources.MenuBackgroundTexture());

        InitUI(m_ui, m_resources.UiFont(), m_resources.TitleFont());

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
        m_player.Reset(m_resources.PlayerTexture());
        m_apple.Respawn(m_resources.AppleTexture());

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
        m_player.AddSpeed(PlayerConfig::Acceleration);

        m_audio.PlayEatApple();
        m_apple.Respawn(m_resources.AppleTexture());
    }

    void Game::UpdatePlaying(float dt)
    {
        m_player.HandleInput();
        m_player.Update(dt);

        if (m_player.HasCollisionWithScreenBorder())
        {
            m_mode = EGameMode::GameOver;
            m_ui.blinkTimerSeconds = 0.0F;
            return;
        }

        if (IsCirclesCollide(
            m_player.Position(), m_player.Radius(),
            m_apple.Position(), m_apple.Radius()))
        {
            OnAppleEaten();
        }
    }

    void Game::Update(float dt)
    {
        switch (m_mode)
        {
        case EGameMode::MainMenu:
            UpdateMenuUI(m_ui, dt);
            break;

        case EGameMode::Playing:
            UpdatePlaying(dt);
            break;

        case EGameMode::GameOver:
            UpdateGameOverUI(m_ui, dt);
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

        window.draw(m_backgroundSprite);

        m_player.Draw(window);
        m_apple.Draw(window);

        DrawUI(m_ui, window);

        if (m_mode == EGameMode::GameOver)
        {
            DrawGameOverOverlay(m_ui, window);
        }
    }
}
