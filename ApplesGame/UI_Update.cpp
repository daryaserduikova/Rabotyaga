#include "UI.h"
#include "UI_Common.h"
#include "Constants.h"

namespace ApplesGame
{
    void UpdateUI(UIState& ui, const UIModel& model)
    {
        switch (model.mode)
        {
        case EGameMode::MainMenu:
        {
            ui.mainTitleText.setString("RABOTYAGA");
            CenterText(ui.mainTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_MainTitleY);

            ui.playText.setString(MakeMenuLine(model.mainMenuIndex == 0, "Play"));
            ui.exitText.setString(MakeMenuLine(model.mainMenuIndex == 1, "Exit"));

            CenterText(ui.playText, Screen::k_WidthF * 0.5f, UIConfig::k_MainPlayY);
            CenterText(ui.exitText, Screen::k_WidthF * 0.5f, UIConfig::k_MainExitY);
            break;
        }

        case EGameMode::ChooseMode:
        {
            const bool finite20 = HasRule(model.rules, EGameRule::Finite20);
            const bool finite50 = HasRule(model.rules, EGameRule::Finite50);
            const bool infinite = HasRule(model.rules, EGameRule::InfiniteApples);
            const bool speedUp = HasRule(model.rules, EGameRule::SpeedUpOnEat);
            const bool noSpeedUp = HasRule(model.rules, EGameRule::NoSpeedUpOnEat);

            ui.chooseTitleText.setString("CHOOSE MODE");
            CenterText(ui.chooseTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_ChooseTitleY);

            ui.chooseApplesHeaderText.setString("Apples:");
            ui.chooseFinite20Text.setString(MakeChooseLine(model.chooseIndex == 0, finite20, "1 - Finite (20)"));
            ui.chooseFinite50Text.setString(MakeChooseLine(model.chooseIndex == 1, finite50, "2 - Finite (50)"));
            ui.chooseInfiniteText.setString(MakeChooseLine(model.chooseIndex == 2, infinite, "3 - Infinite"));

            ui.chooseSpeedHeaderText.setString("Speed:");
            ui.chooseSpeedUpText.setString(MakeChooseLine(model.chooseIndex == 3, speedUp, "4 - Speed up on eat"));
            ui.chooseNoSpeedUpText.setString(MakeChooseLine(model.chooseIndex == 4, noSpeedUp, "5 - No speed up"));

            ui.chooseStartText.setString(MakeMenuLine(model.chooseIndex == 5, "START"));

            const float x = UIConfig::k_ChooseListLeftX;
            const float y = UIConfig::k_ChooseListTopY;
            const float line = UIConfig::k_ChooseLineStep;

            LeftAlignText(ui.chooseApplesHeaderText, x, y);
            LeftAlignText(ui.chooseFinite20Text, x, y + line * 1.0f);
            LeftAlignText(ui.chooseFinite50Text, x, y + line * 2.0f);
            LeftAlignText(ui.chooseInfiniteText, x, y + line * 3.0f);

            LeftAlignText(ui.chooseSpeedHeaderText, x, y + line * UIConfig::k_ChooseSpeedHeaderLine);
            LeftAlignText(ui.chooseSpeedUpText, x, y + line * UIConfig::k_ChooseSpeedUpLine);
            LeftAlignText(ui.chooseNoSpeedUpText, x, y + line * UIConfig::k_ChooseNoSpeedUpLine);

            LeftAlignText(ui.chooseStartText, x, y + line * UIConfig::k_ChooseStartLine);
            break;
        }

        case EGameMode::Playing:
        {
            ui.scoreText.setString("Score: " + std::to_string(model.score));
            ui.scoreText.setPosition(UIConfig::k_HudScoreX, UIConfig::k_HudScoreY);
            break;
        }

        case EGameMode::GameOver:
        {
            ui.scoreText.setString("Score: " + std::to_string(model.score));
            ui.scoreText.setPosition(UIConfig::k_HudScoreX, UIConfig::k_HudScoreY);

            ui.gameOverTitleText.setString("GAME OVER");
            CenterText(ui.gameOverTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_GameOverTitleY);

            std::string menu;
            menu += MakeMenuLine(model.gameOverIndex == 0, "Restart");
            menu += "\n";
            menu += MakeMenuLine(model.gameOverIndex == 1, "Leaderboard");
            menu += "\n";
            menu += MakeMenuLine(model.gameOverIndex == 2, "Exit");

            ui.gameOverMenuText.setString(menu);
            CenterText(ui.gameOverMenuText, Screen::k_WidthF * 0.5f, UIConfig::k_GameOverMenuY);
            break;
        }

        case EGameMode::Leaderboard:
        {
            ui.leaderboardTitleText.setString("LEADERBOARD");
            CenterText(ui.leaderboardTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_LeaderboardTitleY);

            for (int i = 0; i < k_MaxLeaderboardEntries; ++i)
            {
                ui.leaderboardEntryTexts[i].setString("");
                ui.leaderboardScoreTexts[i].setString("");
            }

            for (int i = 0; i < model.leaderboardCount; ++i)
            {
                const float y =
                    UIConfig::k_LeaderboardFirstRowY +
                    UIConfig::k_LeaderboardRowStep * static_cast<float>(i);

                ui.leaderboardEntryTexts[i].setString(
                    MakeLeaderboardEntryLine(i + 1, model.leaderboardNames[i]));

                ui.leaderboardScoreTexts[i].setString(
                    std::to_string(model.leaderboardScores[i]));

                LeftAlignText(ui.leaderboardEntryTexts[i], UIConfig::k_LeaderboardLeftX, y);
                RightAlignText(ui.leaderboardScoreTexts[i], UIConfig::k_LeaderboardRightX, y);
            }

            ui.leaderboardBackText.setString("> Back");
            CenterText(ui.leaderboardBackText, Screen::k_WidthF * 0.5f, UIConfig::k_LeaderboardBackY);
            break;
        }
        }
    }
}