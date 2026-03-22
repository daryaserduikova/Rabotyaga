//@file UI_Init.cpp

#include "UI.h"
#include "UI_Common.h"
#include "Constants.h"

namespace ApplesGame
{
    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont)
    {
        // MAIN
        ui.mainTitleText.setFont(titleFont);
        ui.mainTitleText.setCharacterSize(UIConfig::k_TitleSize);
        ui.mainTitleText.setFillColor(UIConfig::k_ColorWhite);
        ui.mainTitleText.setOutlineThickness(UIConfig::k_TitleOutlineThickness);
        ui.mainTitleText.setOutlineColor(UIConfig::k_TitleOutlineColor);

        SetupMenuText(ui.playText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);
        SetupMenuText(ui.leaderboardText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);
        SetupMenuText(ui.exitText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);

        // CHOOSE
        ui.chooseTitleText.setFont(titleFont);
        ui.chooseTitleText.setCharacterSize(UIConfig::k_ChooseTitleSize);
        ui.chooseTitleText.setFillColor(UIConfig::k_ColorWhite);
        ui.chooseTitleText.setOutlineThickness(UIConfig::k_TitleOutlineThickness);
        ui.chooseTitleText.setOutlineColor(UIConfig::k_TitleOutlineColor);

        SetupMenuText(ui.chooseApplesHeaderText, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseHeader);
        SetupMenuText(ui.chooseFinite20Text, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseList);
        SetupMenuText(ui.chooseFinite50Text, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseList);
        SetupMenuText(ui.chooseInfiniteText, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseList);
        SetupMenuText(ui.chooseSpeedHeaderText, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseHeader);
        SetupMenuText(ui.chooseSpeedUpText, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseList);
        SetupMenuText(ui.chooseNoSpeedUpText, uiFont, UIConfig::k_ChooseListSize, UIConfig::k_ColorChooseList);
        SetupMenuText(ui.chooseStartText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);

        // HUD
        ui.scoreText.setFont(uiFont);
        ui.scoreText.setCharacterSize(UIConfig::k_HudSize);
        ui.scoreText.setFillColor(UIConfig::k_ColorHud);
        ui.scoreText.setOutlineThickness(1.0f);
        ui.scoreText.setOutlineColor(UIConfig::k_TextOutlineColor);

        // GAME OVER
        ui.gameOverTitleText.setFont(titleFont);
        ui.gameOverTitleText.setCharacterSize(UIConfig::k_GameOverSize);
        ui.gameOverTitleText.setFillColor(UIConfig::k_ColorGameOver);
        ui.gameOverTitleText.setOutlineThickness(UIConfig::k_GameOverOutlineThickness);
        ui.gameOverTitleText.setOutlineColor(UIConfig::k_GameOverOutlineColor);

        ui.gameOverMenuText.setFont(uiFont);
        ui.gameOverMenuText.setCharacterSize(UIConfig::k_StartSize);
        ui.gameOverMenuText.setFillColor(UIConfig::k_ColorWhite);
        ui.gameOverMenuText.setOutlineThickness(UIConfig::k_TextOutlineThickness);
        ui.gameOverMenuText.setOutlineColor(UIConfig::k_TextOutlineColor);

        // LEADERBOARD
        ui.leaderboardTitleText.setFont(titleFont);
        ui.leaderboardTitleText.setCharacterSize(UIConfig::k_GameOverSize);
        ui.leaderboardTitleText.setFillColor(UIConfig::k_ColorWhite);
        ui.leaderboardTitleText.setOutlineThickness(UIConfig::k_TitleOutlineThickness);
        ui.leaderboardTitleText.setOutlineColor(UIConfig::k_TitleOutlineColor);

        for (int i = 0; i < k_MaxLeaderboardEntries; ++i)
        {
            ui.leaderboardEntryTexts[i].setFont(uiFont);
            ui.leaderboardEntryTexts[i].setCharacterSize(UIConfig::k_LeaderboardSize);
            ui.leaderboardEntryTexts[i].setFillColor(UIConfig::k_ColorWhite);
            ui.leaderboardEntryTexts[i].setOutlineThickness(1.0f);
            ui.leaderboardEntryTexts[i].setOutlineColor(UIConfig::k_TextOutlineColor);

            ui.leaderboardScoreTexts[i].setFont(uiFont);
            ui.leaderboardScoreTexts[i].setCharacterSize(UIConfig::k_LeaderboardSize);
            ui.leaderboardScoreTexts[i].setFillColor(UIConfig::k_ColorWhite);
            ui.leaderboardScoreTexts[i].setOutlineThickness(1.0f);
            ui.leaderboardScoreTexts[i].setOutlineColor(UIConfig::k_TextOutlineColor);
        }

        ui.leaderboardBackText.setFont(uiFont);
        ui.leaderboardBackText.setCharacterSize(UIConfig::k_StartSize);
        ui.leaderboardBackText.setFillColor(UIConfig::k_ColorStartActive);
        ui.leaderboardBackText.setOutlineThickness(UIConfig::k_TextOutlineThickness);
        ui.leaderboardBackText.setOutlineColor(UIConfig::k_TextOutlineColor);

        // PAUSE
        ui.pauseTitleText.setFont(titleFont);
        ui.pauseTitleText.setCharacterSize(UIConfig::k_GameOverSize);
        ui.pauseTitleText.setFillColor(UIConfig::k_ColorWhite);
        ui.pauseTitleText.setOutlineThickness(UIConfig::k_TitleOutlineThickness);
        ui.pauseTitleText.setOutlineColor(UIConfig::k_TitleOutlineColor);

        SetupMenuText(ui.pauseContinueText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);
        SetupMenuText(ui.pauseExitText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);
    }
}