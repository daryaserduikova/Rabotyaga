// @file Game.cpp

#include "Game.h"

#include <cstdlib>

#include "Constants.h"
#include "MathUtils.h"
#include "RenderHelpers.h"

namespace ApplesGame
{
    namespace
    {
        constexpr const char* k_PlayerName = "Player";

        constexpr int k_FakePlayersCount = 6;

        constexpr const char* k_FakePlayerNames[k_FakePlayersCount] =
        {
            "Rodion",
            "Tikhon",
            "Missha",
            "Dassha",
            "Sergey",
            "Alla"
        };

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

        bool IsBackKey(sf::Keyboard::Key key)
        {
            return IsConfirmKey(key) || key == sf::Keyboard::Escape;
        }

        int MoveMenuIndex(int index, int count, bool up, bool down)
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

        int MakeRandomLeaderboardScore()
        {
            return 30 + (std::rand() % 121);
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

        m_Background.setTexture(m_Resources.BackgroundTexture());
        FitSpriteToScreen(m_Background);

        m_MenuSprites.main.setTexture(m_Resources.MenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.main);

        m_MenuSprites.choose.setTexture(m_Resources.ChooseMenuBackgroundTexture());
        FitSpriteToScreen(m_MenuSprites.choose);

        InitUI(m_Ui, m_Resources.UiFont(), m_Resources.TitleFont());

        EnsureDefaultRules();
        GenerateLeaderboard();

        m_Mode = EGameMode::MainMenu;
        m_RequestExit = false;
        m_MainMenuIndex = 0;
        m_ChooseIndex = k_ChooseStartIndex;
        m_GameOverIndex = 0;
        m_Score = 0;

        return true;
    }

    void Game::Shutdown()
    {
        FreeApples();
        m_Audio.Shutdown();
    }

    void Game::ResetGameplay()
    {
        m_Player.Reset(m_Resources.PlayerTexture());
        m_Score = 0;
        AllocateApples(GetInitialAppleCountFromRules());
    }

    void Game::Update(float dtSeconds)
    {
        if (m_Mode == EGameMode::Playing)
        {
            UpdatePlaying(dtSeconds);
        }

        const std::vector<Record> sorted = BuildSortedLeaderboardRecords();

        UIModel model{};
        model.mode = m_Mode;
        model.score = m_Score;
        model.mainMenuIndex = m_MainMenuIndex;
        model.chooseIndex = m_ChooseIndex;
        model.gameOverIndex = m_GameOverIndex;
        model.rules = m_Rules;

        const int count = static_cast<int>(sorted.size());

        model.leaderboardCount =
            count < k_MaxLeaderboardEntries
            ? count
            : k_MaxLeaderboardEntries;

        for (int i = 0; i < model.leaderboardCount; ++i)
        {
            model.leaderboardNames[i] = sorted[i].name;
            model.leaderboardScores[i] = sorted[i].score;
        }

        UpdateUI(m_Ui, model);
    }

    void Game::Draw(sf::RenderWindow& window)
    {
        switch (m_Mode)
        {
        case EGameMode::MainMenu:
            DrawMainMenu(m_Ui, window, m_MenuSprites.main);
            return;

        case EGameMode::ChooseMode:
            DrawChooseMode(m_Ui, window, m_MenuSprites.choose);
            return;

        case EGameMode::Leaderboard:
            DrawLeaderboard(m_Ui, window, m_Background);
            return;

        case EGameMode::Playing:
        case EGameMode::GameOver:
            break;
        }

        window.draw(m_Background);

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

    void Game::FreeApples()
    {
        delete[] m_Apples;
        m_Apples = nullptr;
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

    void Game::OnAppleEaten(int index)
    {
        ++m_Score;

        m_Audio.PlayEatApple();

        if (HasRule(m_Rules, EGameRule::SpeedUpOnEat) &&
            !HasRule(m_Rules, EGameRule::NoSpeedUpOnEat))
        {
            m_Player.AddSpeed(PlayerConfig::k_Acceleration);
        }

        if (IsInfiniteMode())
        {
            m_Apples[index].Respawn(m_Resources.AppleTexture());
            return;
        }

        for (int i = index; i < m_ApplesCount - 1; ++i)
        {
            m_Apples[i] = m_Apples[i + 1];
        }

        --m_ApplesCount;

        if (m_ApplesCount <= 0)
        {
            EnterGameOver();
        }
    }

    void Game::EnsureDefaultRules()
    {
        if (!HasRule(m_Rules, EGameRule::Finite20) &&
            !HasRule(m_Rules, EGameRule::Finite50) &&
            !HasRule(m_Rules, EGameRule::InfiniteApples))
        {
            m_Rules |= EGameRule::InfiniteApples;
        }

        if (!HasRule(m_Rules, EGameRule::SpeedUpOnEat) &&
            !HasRule(m_Rules, EGameRule::NoSpeedUpOnEat))
        {
            m_Rules |= EGameRule::SpeedUpOnEat;
        }
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

        return 10;
    }

    bool Game::IsInfiniteMode() const
    {
        return HasRule(m_Rules, EGameRule::InfiniteApples);
    }

    void Game::ApplyChooseSelection()
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

        default:
            break;
        }
    }

    void Game::GenerateLeaderboard()
    {
        m_Leaderboard.clear();

        for (int i = 0; i < k_FakePlayersCount; ++i)
        {
            m_Leaderboard[k_FakePlayerNames[i]] = MakeRandomLeaderboardScore();
        }

        m_Leaderboard[k_PlayerName] = 0;
    }

    void Game::UpdatePlayerLeaderboard()
    {
        m_Leaderboard[k_PlayerName] = m_Score;
    }

    std::vector<Record> Game::BuildSortedLeaderboardRecords() const
    {
        std::vector<Record> records;
        records.reserve(m_Leaderboard.size());

        for (auto it = m_Leaderboard.begin(); it != m_Leaderboard.end(); ++it)
        {
            Record r;
            r.name = it->first;
            r.score = it->second;
            records.push_back(r);
        }

        SortRecordsDescending(records);

        return records;
    }

    void Game::SortRecordsDescending(std::vector<Record>& records)
    {
        const int count = static_cast<int>(records.size());

        for (int i = 0; i < count - 1; ++i)
        {
            for (int j = 0; j < count - 1 - i; ++j)
            {
                if (records[j].score < records[j + 1].score)
                {
                    Record temp = records[j];
                    records[j] = records[j + 1];
                    records[j + 1] = temp;
                }
            }
        }
    }

    void Game::UpdatePlaying(float dtSeconds)
    {
        m_Player.HandleInput();
        m_Player.Update(dtSeconds);

        if (m_Player.HasCollisionWithScreenBorder())
        {
            EnterGameOver();
            return;
        }

        for (int i = 0; i < m_ApplesCount; ++i)
        {
            if (IsCirclesCollide(
                m_Player.Position(), m_Player.Radius(),
                m_Apples[i].Position(), m_Apples[i].Radius()))
            {
                OnAppleEaten(i);

                if (!IsInfiniteMode())
                {
                    --i;
                }
            }
        }
    }

    void Game::EnterGameOver()
    {
        UpdatePlayerLeaderboard();

        m_GameOverIndex = 0;
        m_Mode = EGameMode::GameOver;
    }

    void Game::HandleMainMenuInput(sf::Keyboard::Key key)
    {
        m_MainMenuIndex = MoveMenuIndex(
            m_MainMenuIndex,
            k_MainMenuCount,
            IsUpKey(key),
            IsDownKey(key));

        if (!IsConfirmKey(key))
        {
            return;
        }

        if (m_MainMenuIndex == 0)
        {
            m_Mode = EGameMode::ChooseMode;
            m_ChooseIndex = k_ChooseStartIndex;
        }
        else
        {
            m_RequestExit = true;
        }
    }

    void Game::HandleChooseModeInput(sf::Keyboard::Key key)
    {
        m_ChooseIndex = MoveMenuIndex(
            m_ChooseIndex,
            k_ChooseMenuCount,
            IsUpKey(key),
            IsDownKey(key));

        if (!IsConfirmKey(key))
        {
            return;
        }

        if (m_ChooseIndex == k_ChooseStartIndex)
        {
            ResetGameplay();
            m_Mode = EGameMode::Playing;
        }
        else
        {
            ApplyChooseSelection();
        }
    }

    void Game::HandleGameOverInput(sf::Keyboard::Key key)
    {
        m_GameOverIndex = MoveMenuIndex(
            m_GameOverIndex,
            k_GameOverCount,
            IsUpKey(key),
            IsDownKey(key));

        if (!IsConfirmKey(key))
        {
            return;
        }

        if (m_GameOverIndex == 0)
        {
            ResetGameplay();
            m_Mode = EGameMode::Playing;
        }
        else if (m_GameOverIndex == 1)
        {
            m_Mode = EGameMode::Leaderboard;
        }
        else
        {
            m_Mode = EGameMode::MainMenu;
        }
    }

    void Game::HandleLeaderboardInput(sf::Keyboard::Key key)
    {
        if (IsBackKey(key))
        {
            m_Mode = EGameMode::GameOver;
        }
    }

    void Game::HandleEvent(const sf::Event& event)
    {
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        const sf::Keyboard::Key key = event.key.code;

        switch (m_Mode)
        {
        case EGameMode::MainMenu:
            HandleMainMenuInput(key);
            break;

        case EGameMode::ChooseMode:
            HandleChooseModeInput(key);
            break;

        case EGameMode::GameOver:
            HandleGameOverInput(key);
            break;

        case EGameMode::Leaderboard:
            HandleLeaderboardInput(key);
            break;

        default:
            break;
        }
    }
}