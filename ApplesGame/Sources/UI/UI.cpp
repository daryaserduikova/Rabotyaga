// @file UI.cpp

#include "UI.h"

#include <initializer_list>
#include <string>

#include "Constants.h"

namespace ApplesGame
{
    namespace
    {
        constexpr const char* k_MainTitle = "RABOTYAGA";
        constexpr const char* k_PlayText = "Play";
        constexpr const char* k_ExitText = "Exit";

        constexpr const char* k_ChooseTitle = "CHOOSE MODE";
        constexpr const char* k_ChooseApplesHeader = "Apples:";
        constexpr const char* k_ChooseSpeedHeader = "Speed:";
        constexpr const char* k_ChooseFinite20Label = "1 - Finite (20)";
        constexpr const char* k_ChooseFinite50Label = "2 - Finite (50)";
        constexpr const char* k_ChooseInfiniteLabel = "3 - Infinite";
        constexpr const char* k_ChooseSpeedUpLabel = "4 - Speed up on eat";
        constexpr const char* k_ChooseNoSpeedUpLabel = "5 - No speed up";
        constexpr const char* k_ChooseStartLabel = "START";

        constexpr const char* k_GameOverTitle = "GAME OVER";
        constexpr const char* k_GameOverRestart = "Restart";
        constexpr const char* k_GameOverLeaderboard = "Leaderboard";

        constexpr const char* k_LeaderboardTitle = "LEADERBOARD";
        constexpr const char* k_LeaderboardBack = "> Back";

        void CenterText(sf::Text& text, float x, float y)
        {
            const sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(
                bounds.left + bounds.width * 0.5f,
                bounds.top + bounds.height * 0.5f);
            text.setPosition(x, y);
        }

        void LeftAlignText(sf::Text& text, float x, float y)
        {
            const sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.left, bounds.top);
            text.setPosition(x, y);
        }

        void RightAlignText(sf::Text& text, float x, float y)
        {
            const sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.left + bounds.width, bounds.top);
            text.setPosition(x, y);
        }

        const char* Check(bool value)
        {
            return value ? "[x] " : "[ ] ";
        }

        std::string MakeMenuLine(bool selected, const std::string& text)
        {
            return std::string(selected ? "> " : "  ") + text;
        }

        std::string MakeChooseLine(bool selected, bool checked, const std::string& label)
        {
            return std::string(selected ? "> " : "  ") + Check(checked) + label;
        }

        std::string MakeLeaderboardEntryLine(int place, const std::string& name)
        {
            std::string line = std::to_string(place) + ". " + name + " ";
            while (line.size() < 50)
            {
                line += '.';
            }
            return line;
        }

        void SetupMenuText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& color)
        {
            text.setFont(font);
            text.setCharacterSize(size);
            text.setFillColor(color);
            text.setOutlineThickness(0.0f);
            text.setOutlineColor(UIConfig::k_TextOutlineColor);
        }

        void SetSelectedStyle(
            sf::Text& text,
            bool selected,
            const sf::Color& baseColor,
            const sf::Color& selectedColor)
        {
            text.setFillColor(selected ? selectedColor : baseColor);

            if (selected)
            {
                text.setOutlineThickness(UIConfig::k_TextOutlineThickness);
                text.setOutlineColor(UIConfig::k_TextOutlineColor);
            }
            else
            {
                text.setOutlineThickness(0.0f);
            }
        }

        struct TextSelectionStyle
        {
            sf::Text* text = nullptr;
            bool selected = false;
            sf::Color baseColor = sf::Color::White;
            sf::Color selectedColor = sf::Color::White;
        };

        void ApplySelectionStyles(const std::initializer_list<TextSelectionStyle>& styles)
        {
            for (const TextSelectionStyle& style : styles)
            {
                if (style.text != nullptr)
                {
                    SetSelectedStyle(
                        *style.text,
                        style.selected,
                        style.baseColor,
                        style.selectedColor);
                }
            }
        }

        void UpdateMainMenuUI(UIState& ui, const UIModel& model)
        {
            ui.mainTitleText.setString(k_MainTitle);
            CenterText(ui.mainTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_MainTitleY);

            ui.playText.setString(MakeMenuLine(model.mainMenuIndex == 0, k_PlayText));
            ui.exitText.setString(MakeMenuLine(model.mainMenuIndex == 1, k_ExitText));

            ApplySelectionStyles({
                { &ui.playText, model.mainMenuIndex == 0, UIConfig::k_ColorStart, UIConfig::k_ColorStartActive },
                { &ui.exitText, model.mainMenuIndex == 1, UIConfig::k_ColorStart, UIConfig::k_ColorStartActive }
                });

            CenterText(ui.playText, Screen::k_WidthF * 0.5f, UIConfig::k_MainPlayY);
            CenterText(ui.exitText, Screen::k_WidthF * 0.5f, UIConfig::k_MainExitY);
        }

        void UpdateChooseMenuUI(UIState& ui, const UIModel& model)
        {
            const bool finite20 = HasRule(model.rules, EGameRule::Finite20);
            const bool finite50 = HasRule(model.rules, EGameRule::Finite50);
            const bool infinite = HasRule(model.rules, EGameRule::InfiniteApples);
            const bool speedUp = HasRule(model.rules, EGameRule::SpeedUpOnEat);
            const bool noSpeedUp = HasRule(model.rules, EGameRule::NoSpeedUpOnEat);

            ui.chooseTitleText.setString(k_ChooseTitle);
            CenterText(ui.chooseTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_ChooseTitleY);

            ui.chooseApplesHeaderText.setString(k_ChooseApplesHeader);
            ui.chooseFinite20Text.setString(MakeChooseLine(model.chooseIndex == 0, finite20, k_ChooseFinite20Label));
            ui.chooseFinite50Text.setString(MakeChooseLine(model.chooseIndex == 1, finite50, k_ChooseFinite50Label));
            ui.chooseInfiniteText.setString(MakeChooseLine(model.chooseIndex == 2, infinite, k_ChooseInfiniteLabel));

            ui.chooseSpeedHeaderText.setString(k_ChooseSpeedHeader);
            ui.chooseSpeedUpText.setString(MakeChooseLine(model.chooseIndex == 3, speedUp, k_ChooseSpeedUpLabel));
            ui.chooseNoSpeedUpText.setString(MakeChooseLine(model.chooseIndex == 4, noSpeedUp, k_ChooseNoSpeedUpLabel));

            ui.chooseStartText.setString(MakeMenuLine(model.chooseIndex == 5, k_ChooseStartLabel));

            ApplySelectionStyles({
                { &ui.chooseFinite20Text, model.chooseIndex == 0, UIConfig::k_ColorChooseList, UIConfig::k_ColorChooseListActive },
                { &ui.chooseFinite50Text, model.chooseIndex == 1, UIConfig::k_ColorChooseList, UIConfig::k_ColorChooseListActive },
                { &ui.chooseInfiniteText, model.chooseIndex == 2, UIConfig::k_ColorChooseList, UIConfig::k_ColorChooseListActive },
                { &ui.chooseSpeedUpText, model.chooseIndex == 3, UIConfig::k_ColorChooseList, UIConfig::k_ColorChooseListActive },
                { &ui.chooseNoSpeedUpText, model.chooseIndex == 4, UIConfig::k_ColorChooseList, UIConfig::k_ColorChooseListActive },
                { &ui.chooseStartText, model.chooseIndex == 5, UIConfig::k_ColorStart, UIConfig::k_ColorStartActive }
                });

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
        }

        void UpdateHudUI(UIState& ui, const UIModel& model)
        {
            ui.scoreText.setString("Score: " + std::to_string(model.score));
            ui.scoreText.setPosition(UIConfig::k_HudScoreX, UIConfig::k_HudScoreY);
        }

        void UpdateGameOverUI(UIState& ui, const UIModel& model)
        {
            ui.gameOverTitleText.setString(k_GameOverTitle);
            CenterText(ui.gameOverTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_GameOverTitleY);

            ui.gameOverMenuText.setString(
                model.gameOverIndex == 0
                ? MakeMenuLine(true, k_GameOverRestart) + "\n" + MakeMenuLine(false, k_GameOverLeaderboard) + "\n" + MakeMenuLine(false, k_ExitText)
                : model.gameOverIndex == 1
                ? MakeMenuLine(false, k_GameOverRestart) + "\n" + MakeMenuLine(true, k_GameOverLeaderboard) + "\n" + MakeMenuLine(false, k_ExitText)
                : MakeMenuLine(false, k_GameOverRestart) + "\n" + MakeMenuLine(false, k_GameOverLeaderboard) + "\n" + MakeMenuLine(true, k_ExitText));

            CenterText(ui.gameOverMenuText, Screen::k_WidthF * 0.5f, UIConfig::k_GameOverMenuY);
        }

        void UpdateLeaderboardUI(UIState& ui, const UIModel& model)
        {
            ui.leaderboardTitleText.setString(k_LeaderboardTitle);
            CenterText(ui.leaderboardTitleText, Screen::k_WidthF * 0.5f, UIConfig::k_LeaderboardTitleY);

            for (int i = 0; i < k_MaxLeaderboardEntries; ++i)
            {
                ui.leaderboardEntryTexts[i].setString("");
                ui.leaderboardScoreTexts[i].setString("");
            }

            for (int i = 0; i < model.leaderboardCount; ++i)
            {
                ui.leaderboardEntryTexts[i].setString(
                    MakeLeaderboardEntryLine(i + 1, model.leaderboardNames[i]));

                ui.leaderboardScoreTexts[i].setString(
                    std::to_string(model.leaderboardScores[i]));

                const float y = UIConfig::k_LeaderboardFirstRowY + UIConfig::k_LeaderboardRowStep * static_cast<float>(i);

                LeftAlignText(ui.leaderboardEntryTexts[i], UIConfig::k_LeaderboardLeftX, y);
                RightAlignText(ui.leaderboardScoreTexts[i], UIConfig::k_LeaderboardRightX, y);
            }

            ui.leaderboardBackText.setString(k_LeaderboardBack);
            CenterText(ui.leaderboardBackText, Screen::k_WidthF * 0.5f, UIConfig::k_LeaderboardBackY);
        }
    }

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont)
    {
        // Main
        ui.mainTitleText.setFont(titleFont);
        ui.mainTitleText.setCharacterSize(UIConfig::k_TitleSize);
        ui.mainTitleText.setFillColor(UIConfig::k_ColorWhite);
        ui.mainTitleText.setOutlineThickness(UIConfig::k_TitleOutlineThickness);
        ui.mainTitleText.setOutlineColor(UIConfig::k_TitleOutlineColor);

        SetupMenuText(ui.playText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);
        SetupMenuText(ui.exitText, uiFont, UIConfig::k_StartSize, UIConfig::k_ColorStart);

        // Choose
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

        // GameOver
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

        // Leaderboard
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
    }

    void UpdateUI(UIState& ui, const UIModel& model)
    {
        switch (model.mode)
        {
        case EGameMode::MainMenu:
            UpdateMainMenuUI(ui, model);
            break;

        case EGameMode::ChooseMode:
            UpdateChooseMenuUI(ui, model);
            break;

        case EGameMode::Playing:
            UpdateHudUI(ui, model);
            break;

        case EGameMode::GameOver:
            UpdateHudUI(ui, model);
            UpdateGameOverUI(ui, model);
            break;

        case EGameMode::Leaderboard:
            UpdateLeaderboardUI(ui, model);
            break;
        }
    }

    void DrawMainMenu(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background)
    {
        window.draw(background);
        window.draw(ui.mainTitleText);
        window.draw(ui.playText);
        window.draw(ui.exitText);
    }

    void DrawChooseMode(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background)
    {
        window.draw(background);
        window.draw(ui.chooseTitleText);
        window.draw(ui.chooseApplesHeaderText);
        window.draw(ui.chooseFinite20Text);
        window.draw(ui.chooseFinite50Text);
        window.draw(ui.chooseInfiniteText);
        window.draw(ui.chooseSpeedHeaderText);
        window.draw(ui.chooseSpeedUpText);
        window.draw(ui.chooseNoSpeedUpText);
        window.draw(ui.chooseStartText);
    }

    void DrawHud(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
    }

    void DrawGameOver(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.gameOverTitleText);
        window.draw(ui.gameOverMenuText);
    }

    void DrawLeaderboard(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background)
    {
        window.draw(background);
        window.draw(ui.leaderboardTitleText);

        for (int i = 0; i < k_MaxLeaderboardEntries; ++i)
        {
            window.draw(ui.leaderboardEntryTexts[i]);
            window.draw(ui.leaderboardScoreTexts[i]);
        }

        window.draw(ui.leaderboardBackText);
    }
}