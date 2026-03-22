//@file Game.cpp

#include "Game.h"

#include "Constants.h"
#include "MathUtils.h"
#include "RenderHelpers.h"

namespace ApplesGame
{
    namespace
    {
        constexpr float k_SpeedUpAmount = 20.0F;

        bool IsRightPressed()
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        }

        bool IsLeftPressed()
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        }

        bool IsUpPressed()
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        }

        bool IsDownPressed()
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        }

        bool IsUpKey(sf::Keyboard::Key key)
        {
            return key == sf::Keyboard::Up || key == sf::Keyboard::W;
        }

        bool IsDownKey(sf::Keyboard::Key key)
        {
            return key == sf::Keyboard::Down || key == sf::Keyboard::S;
        }

        bool IsConfirmKey(sf::Keyboard::Key key)
        {
            return key == sf::Keyboard::Enter || key == sf::Keyboard::Space;
        }

        int MoveIndex(int index, int count, bool up, bool down)
        {
            if (count <= 0)
            {
                return 0;
            }

            if (up)
            {
                return (index - 1 + count) % count;
            }

            if (down)
            {
                return (index + 1) % count;
            }

            return index;
        }

        void HandleMenuNavigation(int& index, int count, sf::Keyboard::Key key)
        {
            index = MoveIndex(index, count, IsUpKey(key), IsDownKey(key));
        }
    }

    bool Game::Init()
    {
        if (!m_Resources.Load(Paths::k_Resources))
        {
            return false;
        }

        if (!m_Audio.Init(Paths::k_Resources))
        {
            return false;
        }

        m_Audio.PlayMusic();

        m_Background.setTexture(m_Resources.BackgroundTexture());
        FitSpriteToScreen(m_Background);

        m_MenuSprites.main.setTexture(m_Resources.MenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.main);

        m_MenuSprites.choose.setTexture(m_Resources.ChooseMenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.choose);

        InitUI(m_Ui, m_Resources.UiFont(), m_Resources.TitleFont());

        m_Rules = EGameRule::InfiniteApples | EGameRule::SpeedUpOnEat;

        m_Leaderboard.Load();

        m_Mode = EGameMode::MainMenu;
        m_RequestExit = false;

        m_MainMenuIndex = 0;
        m_ChooseIndex = 5;
        m_GameOverIndex = 0;
        m_PauseIndex = 0;

        m_Score = 0;

        return true;
    }

    void Game::Shutdown()
    {
        m_Audio.Shutdown();
    }

    void Game::ResetGameplay()
    {
        m_Player.Reset(m_Resources.PlayerTexture());
        m_Score = 0;
        m_PauseIndex = 0;

        int applesCount = 10;

        if (HasRule(m_Rules, EGameRule::Finite20))
        {
            applesCount = 20;
        }
        else if (HasRule(m_Rules, EGameRule::Finite50))
        {
            applesCount = 50;
        }

        m_Apples.clear();
        m_Apples.resize(static_cast<size_t>(applesCount));

        for (auto& apple : m_Apples)
        {
            apple.Respawn(m_Resources.AppleTexture());
        }
    }

    void Game::UpdatePlaying(float dtSeconds)
    {
        if (IsRightPressed())
        {
            m_Player.SetDirection(EPlayerDirection::Right);
        }
        else if (IsUpPressed())
        {
            m_Player.SetDirection(EPlayerDirection::Up);
        }
        else if (IsLeftPressed())
        {
            m_Player.SetDirection(EPlayerDirection::Left);
        }
        else if (IsDownPressed())
        {
            m_Player.SetDirection(EPlayerDirection::Down);
        }

        m_Player.Update(dtSeconds);

        if (m_Player.HasCollisionWithScreenBorder())
        {
            EnterGameOver();
            return;
        }

        for (auto& apple : m_Apples)
        {
            if (IsCirclesCollide(
                m_Player.Position(), m_Player.Radius(),
                apple.Position(), apple.Radius()))
            {
                ++m_Score;
                m_Audio.PlayEatApple();

                if (HasRule(m_Rules, EGameRule::SpeedUpOnEat) &&
                    !HasRule(m_Rules, EGameRule::NoSpeedUpOnEat))
                {
                    m_Player.AddSpeed(k_SpeedUpAmount);
                }

                apple.Respawn(m_Resources.AppleTexture());
            }
        }
    }

    void Game::Update(float dtSeconds)
    {
        switch (m_Mode)
        {
        case EGameMode::Playing:
            UpdatePlaying(dtSeconds);
            break;

        case EGameMode::MainMenu:
        case EGameMode::ChooseMode:
        case EGameMode::GameOver:
        case EGameMode::Leaderboard:
        case EGameMode::Pause:
        default:
            break;
        }

        const auto& sorted = m_Leaderboard.GetSorted();

        m_UiModel.mode = m_Mode;
        m_UiModel.score = m_Score;
        m_UiModel.mainMenuIndex = m_MainMenuIndex;
        m_UiModel.chooseIndex = m_ChooseIndex;
        m_UiModel.gameOverIndex = m_GameOverIndex;
        m_UiModel.pauseIndex = m_PauseIndex;
        m_UiModel.rules = m_Rules;

        const int count = static_cast<int>(sorted.size());
        m_UiModel.leaderboardCount =
            (count < k_MaxLeaderboardEntries) ? count : k_MaxLeaderboardEntries;

        for (int i = 0; i < k_MaxLeaderboardEntries; ++i)
        {
            m_UiModel.leaderboardNames[i].clear();
            m_UiModel.leaderboardScores[i] = 0;
        }

        for (int i = 0; i < m_UiModel.leaderboardCount; ++i)
        {
            m_UiModel.leaderboardNames[i] = sorted[i].name;
            m_UiModel.leaderboardScores[i] = sorted[i].score;
        }

        UpdateUI(m_Ui, m_UiModel);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        if (m_Mode == EGameMode::MainMenu)
        {
            DrawMainMenu(m_Ui, window, m_MenuSprites.main);
            return;
        }

        if (m_Mode == EGameMode::ChooseMode)
        {
            DrawChooseMode(m_Ui, window, m_MenuSprites.choose);
            return;
        }

        if (m_Mode == EGameMode::Leaderboard)
        {
            DrawLeaderboard(m_Ui, window, m_Background);
            return;
        }

        window.draw(m_Background);

        m_Player.Draw(window);

        for (auto& apple : m_Apples)
        {
            apple.Draw(window);
        }

        DrawHud(m_Ui, window);

        if (m_Mode == EGameMode::GameOver)
        {
            DrawGameOver(m_Ui, window, m_Background);
        }
        else if (m_Mode == EGameMode::Pause)
        {
            DrawPause(m_Ui, window, m_Background);
        }
    }

    void Game::EnterGameOver()
    {
        m_Leaderboard.UpdatePlayer("Player", m_Score);
        m_Leaderboard.Save();

        m_GameOverIndex = 0;
        m_Mode = EGameMode::GameOver;
    }

    void Game::HandleEvent(const sf::Event& event)
    {
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        const sf::Keyboard::Key key = event.key.code;

        if (key == sf::Keyboard::Escape)
        {
            if (m_Mode == EGameMode::Playing)
            {
                m_PauseIndex = 0;
                m_Mode = EGameMode::Pause;
                return;
            }

            if (m_Mode == EGameMode::Pause)
            {
                m_Mode = EGameMode::Playing;
                return;
            }
        }

        switch (m_Mode)
        {
        case EGameMode::MainMenu:
        {
            HandleMenuNavigation(m_MainMenuIndex, k_MainMenuCount, key);

            if (IsConfirmKey(key))
            {
                if (m_MainMenuIndex == 0)
                {
                    m_Mode = EGameMode::ChooseMode;
                }
                else if (m_MainMenuIndex == 1)
                {
                    m_Mode = EGameMode::Leaderboard;
                }
                else if (m_MainMenuIndex == 2)
                {
                    m_RequestExit = true;
                }
            }
            break;
        }

        case EGameMode::ChooseMode:
        {
            int number = -1;

            if (key == sf::Keyboard::Num1 || key == sf::Keyboard::Numpad1) number = 0;
            else if (key == sf::Keyboard::Num2 || key == sf::Keyboard::Numpad2) number = 1;
            else if (key == sf::Keyboard::Num3 || key == sf::Keyboard::Numpad3) number = 2;
            else if (key == sf::Keyboard::Num4 || key == sf::Keyboard::Numpad4) number = 3;
            else if (key == sf::Keyboard::Num5 || key == sf::Keyboard::Numpad5) number = 4;
            else if (key == sf::Keyboard::Num6 || key == sf::Keyboard::Numpad6) number = 5;

            if (number != -1)
            {
                m_ChooseIndex = number;
            }
            else
            {
                HandleMenuNavigation(m_ChooseIndex, k_ChooseMenuCount, key);
            }

            if (IsConfirmKey(key) || number != -1)
            {
                switch (m_ChooseIndex)
                {
                case 0:
                    SetAppleMode(m_Rules, EGameRule::Finite20);
                    break;

                case 1:
                    SetAppleMode(m_Rules, EGameRule::Finite50);
                    break;

                case 2:
                    SetAppleMode(m_Rules, EGameRule::InfiniteApples);
                    break;

                case 3:
                    SetSpeedMode(m_Rules, EGameRule::SpeedUpOnEat);
                    break;

                case 4:
                    SetSpeedMode(m_Rules, EGameRule::NoSpeedUpOnEat);
                    break;

                case 5:
                    ResetGameplay();
                    m_Mode = EGameMode::Playing;
                    break;

                default:
                    break;
                }
            }
            break;
        }

        case EGameMode::Leaderboard:
        {
            if (key == sf::Keyboard::BackSpace)
            {
                m_Mode = EGameMode::MainMenu;
            }
            break;
        }

        case EGameMode::GameOver:
        {
            HandleMenuNavigation(m_GameOverIndex, k_GameOverCount, key);

            if (IsConfirmKey(key))
            {
                if (m_GameOverIndex == 0)
                {
                    ResetGameplay();
                    m_Mode = EGameMode::Playing;
                }
                else
                {
                    m_Mode = EGameMode::MainMenu;
                }
            }
            break;
        }

        case EGameMode::Pause:
        {
            HandleMenuNavigation(m_PauseIndex, k_PauseMenuCount, key);

            if (IsConfirmKey(key))
            {
                if (m_PauseIndex == 0)
                {
                    m_Mode = EGameMode::Playing;
                }
                else
                {
                    m_Mode = EGameMode::MainMenu;
                }
            }
            break;
        }

        case EGameMode::Playing:
        default:
            break;
        }
    }
}