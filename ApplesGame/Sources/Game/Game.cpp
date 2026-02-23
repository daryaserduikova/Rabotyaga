// @file Game.cpp

#include "Game.h"

#include <algorithm>

#include "Constants.h"
#include "MathUtils.h"
#include "RenderHelpers.h"

namespace ApplesGame
{
    static float Clamp01(float value)
    {
        if (value < 0.0F) return 0.0F;
        if (value > 1.0F) return 1.0F;
        return value;
    }

    static bool IsUpKey(sf::Keyboard::Key key)
    {
        return (key == sf::Keyboard::Up) || (key == sf::Keyboard::W);
    }

    static bool IsDownKey(sf::Keyboard::Key key)
    {
        return (key == sf::Keyboard::Down) || (key == sf::Keyboard::S);
    }

    static bool IsConfirmKey(sf::Keyboard::Key key)
    {
        return (key == sf::Keyboard::Enter) || (key == sf::Keyboard::Space);
    }

    // Cyclic index in [0..count-1]
    static int MoveMenuIndex(int index, int count, bool up, bool down)
    {
        if (count <= 0)
        {
            return 0;
        }

        if (up)
        {
            index = (index - 1 + count) % count;
        }
        else if (down)
        {
            index = (index + 1) % count;
        }

        return index;
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

        m_BackgroundSprite.setTexture(m_Resources.BackgroundTexture());
        FitSpriteToScreen(m_BackgroundSprite);

        // Menu sprites
        m_MenuSprites.main.setTexture(m_Resources.MenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.main);

        m_MenuSprites.choose.setTexture(m_Resources.ChooseMenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.choose);

        // Splash
        m_SplashSprite.setTexture(m_Resources.SplashTexture());
        FitSpriteToScreen(m_SplashSprite);

        InitUI(m_Ui, m_Resources.UiFont(), m_Resources.TitleFont());

        EnsureDefaultRules();

        m_Mode = EGameMode::Splash;
        m_SplashTimerSeconds = 0.0F;
        m_MainMenuIndex = 0;
        m_ChooseIndex = 5;
        m_GameOverIndex = 0;

        return true;
    }

    void Game::Shutdown()
    {
        FreeApples();
        m_Audio.Shutdown();
    }

    void Game::FreeApples()
    {
        if (m_Apples != nullptr)
        {
            delete[] m_Apples;
            m_Apples = nullptr;
        }

        m_ApplesCount = 0;
    }

    void Game::AllocateApples(int count)
    {
        FreeApples();

        if (count <= 0)
        {
            return;
        }

        m_Apples = new Apple[count];
        m_ApplesCount = count;

        for (int i = 0; i < m_ApplesCount; ++i)
        {
            m_Apples[i].Respawn(m_Resources.AppleTexture());
        }
    }

    void Game::EnsureDefaultRules()
    {
        const bool hasAppleMode =
            HasRule(m_Rules, EGameRule::Finite20) ||
            HasRule(m_Rules, EGameRule::Finite50) ||
            HasRule(m_Rules, EGameRule::InfiniteApples);

        if (!hasAppleMode)
        {
            SetAppleMode(m_Rules, EGameRule::InfiniteApples);
        }

        const bool hasSpeedMode =
            HasRule(m_Rules, EGameRule::SpeedUpOnEat) ||
            HasRule(m_Rules, EGameRule::NoSpeedUpOnEat);

        if (!hasSpeedMode)
        {
            SetSpeedMode(m_Rules, EGameRule::SpeedUpOnEat);
        }
    }

    bool Game::IsInfiniteApplesMode() const
    {
        return HasRule(m_Rules, EGameRule::InfiniteApples);
    }

    int Game::GetInitialAppleCountFromRules() const
    {
        if (HasRule(m_Rules, EGameRule::Finite20))
        {
            return 20;
        }

        if (HasRule(m_Rules, EGameRule::Finite50))
        {
            return 50;
        }

        // Infinite: стартовое число, яблоки не заканчиваются (respawn)
        return 10;
    }

    void Game::ResetGameplay()
    {
        m_Player.Reset(m_Resources.PlayerTexture());
        m_Score = 0;
        AllocateApples(GetInitialAppleCountFromRules());
    }

    void Game::ApplyChooseSelection()
    {
        switch (m_ChooseIndex)
        {
        case 0: SetAppleMode(m_Rules, EGameRule::Finite20); break;
        case 1: SetAppleMode(m_Rules, EGameRule::Finite50); break;
        case 2: SetAppleMode(m_Rules, EGameRule::InfiniteApples); break;
        case 3: SetSpeedMode(m_Rules, EGameRule::SpeedUpOnEat); break;
        case 4: SetSpeedMode(m_Rules, EGameRule::NoSpeedUpOnEat); break;
        case 5: break;
        default: break;
        }
    }

    void Game::StartFromChooseMode()
    {
        EnsureDefaultRules();
        ResetGameplay();
        m_Mode = EGameMode::Playing;
    }

    void Game::OnAppleEaten(int appleIndex)
    {
        m_Score++;
        m_Audio.PlayEatApple();

        const bool shouldSpeedUp =
            HasRule(m_Rules, EGameRule::SpeedUpOnEat) &&
            !HasRule(m_Rules, EGameRule::NoSpeedUpOnEat);

        if (shouldSpeedUp)
        {
            m_Player.AddSpeed(PlayerConfig::k_Acceleration);
        }

        if (IsInfiniteApplesMode())
        {
            m_Apples[appleIndex].Respawn(m_Resources.AppleTexture());
            return;
        }

        for (int i = appleIndex; i < m_ApplesCount - 1; ++i)
        {
            m_Apples[i] = m_Apples[i + 1];
        }

        m_ApplesCount--;

        if (m_ApplesCount <= 0)
        {
            m_Mode = EGameMode::GameOver;
            m_GameOverIndex = 0;
        }
    }

    void Game::UpdatePlaying(float dtSeconds)
    {
        m_Player.HandleInput();
        m_Player.Update(dtSeconds);

        if (m_Player.HasCollisionWithScreenBorder())
        {
            m_Mode = EGameMode::GameOver;
            m_GameOverIndex = 0;
            return;
        }

        for (int i = 0; i < m_ApplesCount; ++i)
        {
            if (IsCirclesCollide(
                m_Player.Position(), m_Player.Radius(),
                m_Apples[i].Position(), m_Apples[i].Radius()))
            {
                OnAppleEaten(i);

                if (m_Mode != EGameMode::Playing)
                {
                    return;
                }

                if (!IsInfiniteApplesMode())
                {
                    --i;
                }
            }
        }
    }

    void Game::HandleEvent(const sf::Event& event)
    {
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        const sf::Keyboard::Key key = event.key.code;

        if (m_Mode == EGameMode::Splash)
        {
            if (key == sf::Keyboard::Escape)
            {
                m_RequestExit = true;
                return;
            }

            if (IsConfirmKey(key))
            {
                m_Mode = EGameMode::MainMenu;
                m_MainMenuIndex = 0;
                return;
            }

            return;
        }

        if (m_Mode == EGameMode::MainMenu)
        {
            if (key == sf::Keyboard::Escape)
            {
                m_RequestExit = true;
                return;
            }

            const bool up = IsUpKey(key);
            const bool down = IsDownKey(key);

            const int oldIndex = m_MainMenuIndex;
            m_MainMenuIndex = MoveMenuIndex(m_MainMenuIndex, 2, up, down);
            if (m_MainMenuIndex != oldIndex)
            {
                return;
            }

            if (IsConfirmKey(key))
            {
                if (m_MainMenuIndex == 0)
                {
                    m_Mode = EGameMode::ChooseMode;
                    m_ChooseIndex = 5;
                }
                else
                {
                    m_RequestExit = true;
                }

                return;
            }

            return;
        }

        if (m_Mode == EGameMode::ChooseMode)
        {
            if (key == sf::Keyboard::Escape)
            {
                m_Mode = EGameMode::MainMenu;
                m_MainMenuIndex = 0;
                return;
            }

            const bool up = IsUpKey(key);
            const bool down = IsDownKey(key);

            const int oldIndex = m_ChooseIndex;
            m_ChooseIndex = MoveMenuIndex(m_ChooseIndex, 6, up, down);
            if (m_ChooseIndex != oldIndex)
            {
                return;
            }

            switch (key)
            {
            case sf::Keyboard::Num1: m_ChooseIndex = 0; ApplyChooseSelection(); return;
            case sf::Keyboard::Num2: m_ChooseIndex = 1; ApplyChooseSelection(); return;
            case sf::Keyboard::Num3: m_ChooseIndex = 2; ApplyChooseSelection(); return;
            case sf::Keyboard::Num4: m_ChooseIndex = 3; ApplyChooseSelection(); return;
            case sf::Keyboard::Num5: m_ChooseIndex = 4; ApplyChooseSelection(); return;
            default: break;
            }

            if (IsConfirmKey(key))
            {
                if (m_ChooseIndex == 5)
                {
                    StartFromChooseMode();
                }
                else
                {
                    ApplyChooseSelection();
                }

                return;
            }

            return;
        }

        if (m_Mode == EGameMode::GameOver)
        {
            if (key == sf::Keyboard::Escape)
            {
                m_Mode = EGameMode::MainMenu;
                m_MainMenuIndex = 0;
                return;
            }

            const bool up = IsUpKey(key);
            const bool down = IsDownKey(key);

            const int oldIndex = m_GameOverIndex;
            m_GameOverIndex = MoveMenuIndex(m_GameOverIndex, 2, up, down);
            if (m_GameOverIndex != oldIndex)
            {
                return;
            }

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
                    m_MainMenuIndex = 0;
                }

                return;
            }

            return;
        }
    }

    void Game::Update(float dtSeconds)
    {
        if (m_Mode == EGameMode::Splash)
        {
            m_SplashTimerSeconds += dtSeconds;
        }

        if (m_Mode == EGameMode::Playing)
        {
            UpdatePlaying(dtSeconds);
        }

        UIModel model{};
        model.mode = m_Mode;
        model.score = m_Score;
        model.mainMenuIndex = m_MainMenuIndex;
        model.chooseIndex = m_ChooseIndex;
        model.gameOverIndex = m_GameOverIndex;
        model.rules = m_Rules;

        UpdateUI(m_Ui, model);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        if (m_Mode == EGameMode::Splash)
        {
            const float t01 = Clamp01(m_SplashTimerSeconds / UIConfig::k_SplashFadeSeconds);
            const std::uint8_t alpha = static_cast<std::uint8_t>(t01 * 255.0F);

            DrawSplash(m_Ui, window, m_SplashSprite, alpha, m_SplashTimerSeconds);
            return;
        }

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

        window.draw(m_BackgroundSprite);

        m_Player.Draw(window);

        for (int i = 0; i < m_ApplesCount; ++i)
        {
            m_Apples[i].Draw(window);
        }

        DrawHud(m_Ui, window);

        if (m_Mode == EGameMode::GameOver)
        {
            DrawGameOver(m_Ui, window);
        }
    }
}