// @file UI.cpp

#include "UI.h"

#include <string>
#include <cmath>

#include "Constants.h"
#include "GameRules.h"

namespace ApplesGame
{
    void SetupCenteredText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0F,
            bounds.top + bounds.height / 2.0F);
        text.setPosition(x, y);
    }

    static sf::Text MakeCenteredText(
        const char* str,
        const sf::Font& font,
        unsigned size,
        const sf::Color& color,
        float x,
        float y)
    {
        sf::Text text(str, font, size);
        text.setFillColor(color);
        SetupCenteredText(text, x, y);
        return text;
    }

    static const char* Arrow(bool active) { return active ? "> " : "  "; }
    static const char* Check(bool active) { return active ? "[X] " : "[ ] "; }

    static void SetTextAlpha(sf::Text& text, sf::Uint8 alpha)
    {
        sf::Color c = text.getFillColor();
        c.a = alpha;
        text.setFillColor(c);
    }

    // SUPER SIMPLE: no function objects, just data
    struct ChooseLine
    {
        int index;
        bool checked;
        const char* text;
    };

    static std::string BuildChooseListText(const UIModel& model)
    {
        const bool finite20 = HasRule(model.rules, EGameRule::Finite20);
        const bool finite50 = HasRule(model.rules, EGameRule::Finite50);
        const bool infinite = HasRule(model.rules, EGameRule::InfiniteApples);

        const bool speedUp = HasRule(model.rules, EGameRule::SpeedUpOnEat);
        const bool noSpeed = HasRule(model.rules, EGameRule::NoSpeedUpOnEat);

        const ChooseLine apples[] =
        {
            { 0, finite20,  "1 - Finite (20)" },
            { 1, finite50,  "2 - Finite (50)" },
            { 2, infinite,  "3 - Infinite"   },
        };

        const ChooseLine speed[] =
        {
            { 3, speedUp,   "4 - Speed up on eat" },
            { 4, noSpeed,   "5 - No speed up"     },
        };

        std::string s;

        s += "Apples:\n";
        for (const auto& line : apples)
        {
            const bool active = (model.chooseIndex == line.index);
            s += std::string(Arrow(active)) + Check(line.checked) + line.text + "\n";
        }

        s += "\nSpeed:\n";
        for (const auto& line : speed)
        {
            const bool active = (model.chooseIndex == line.index);
            s += std::string(Arrow(active)) + Check(line.checked) + line.text + "\n";
        }

        return s;
    }

    static std::string BuildGameOverText(const UIModel& model)
    {
        std::string g;
        g += std::string(Arrow(model.gameOverIndex == 0)) + "Restart\n";
        g += std::string(Arrow(model.gameOverIndex == 1)) + "Exit\n";
        return g;
    }

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont)
    {
        const sf::Color white(255, 255, 255);
        const sf::Color hud(255, 255, 255, 160);

        const sf::Color chooseBrown(125, 85, 45);

        ui.scoreText.setFont(uiFont);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(hud);
        ui.scoreText.setPosition(24.0F, 18.0F);

        ui.splashTitleText = MakeCenteredText(
            "RABOTYAGA",
            titleFont,
            54,
            white,
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F - 30.0F
        );

        ui.splashHintText = MakeCenteredText(
            "Press SPACE to Start",
            uiFont,
            22,
            sf::Color(255, 255, 255, 220),
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F + 20.0F
        );

        ui.mainTitleText = MakeCenteredText(
            "RABOTYAGA",
            titleFont,
            48,
            white,
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F - 90.0F
        );

        ui.playText.setFont(uiFont);
        ui.playText.setCharacterSize(28);
        ui.playText.setFillColor(sf::Color(255, 255, 255, 230));
        ui.exitText = ui.playText;

        ui.chooseTitleText = MakeCenteredText(
            "CHOOSE MODE",
            titleFont,
            36,
            white,
            Screen::k_WidthF / 2.0F,
            120.0F
        );

        ui.chooseListText.setFont(uiFont);
        ui.chooseListText.setCharacterSize(20);
        ui.chooseListText.setFillColor(chooseBrown);

        ui.chooseStartText.setFont(uiFont);
        ui.chooseStartText.setString("START");
        ui.chooseStartText.setCharacterSize(34);
        ui.chooseStartText.setStyle(sf::Text::Regular);
        ui.chooseStartText.setOutlineThickness(0.0F);
        ui.chooseStartText.setOutlineColor(sf::Color::Transparent);

        ui.gameOverTitleText = MakeCenteredText(
            "GAME OVER",
            titleFont,
            36,
            sf::Color(255, 0, 0),
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F - 90.0F
        );

        ui.gameOverListText.setFont(uiFont);
        ui.gameOverListText.setCharacterSize(22);
        ui.gameOverListText.setFillColor(sf::Color(255, 255, 255, 230));
    }

    void UpdateUI(UIState& ui, const UIModel& model)
    {
        ui.scoreText.setString("Score: " + std::to_string(model.score));

        ui.playText.setString(model.mainMenuIndex == 0 ? "> Play" : "  Play");
        ui.exitText.setString(model.mainMenuIndex == 1 ? "> Exit" : "  Exit");
        ui.playText.setPosition(Screen::k_WidthF / 2.0F - 60.0F, 260.0F);
        ui.exitText.setPosition(Screen::k_WidthF / 2.0F - 60.0F, 305.0F);

        ui.chooseListText.setString(BuildChooseListText(model));
        SetupCenteredText(
            ui.chooseListText,
            UIConfig::k_ChooseListCenterX,
            UIConfig::k_ChooseListCenterY + UIConfig::k_ChooseListOffsetY
        );

        // START button styling
        const bool startSelected = (model.chooseIndex == 5);

        const sf::Color activeColor(90, 55, 25);
        const sf::Color idleColor(140, 105, 70);
        const sf::Color glowColor(205, 160, 95, 120);

        ui.chooseStartText.setString(startSelected ? "> START <" : "START");
        ui.chooseStartText.setCharacterSize(startSelected ? 38 : 34);
        ui.chooseStartText.setStyle(startSelected ? sf::Text::Bold : sf::Text::Regular);
        ui.chooseStartText.setFillColor(startSelected ? activeColor : idleColor);

        if (startSelected)
        {
            ui.chooseStartText.setOutlineThickness(2.0F);
            ui.chooseStartText.setOutlineColor(glowColor);
        }
        else
        {
            ui.chooseStartText.setOutlineThickness(0.0F);
            ui.chooseStartText.setOutlineColor(sf::Color::Transparent);
        }

        SetupCenteredText(
            ui.chooseStartText,
            UIConfig::k_ChooseListCenterX - 55.0F,
            UIConfig::k_ChooseListCenterY + UIConfig::k_ChooseStartOffsetY - 28.0F
        );

        ui.gameOverListText.setString(BuildGameOverText(model));
        SetupCenteredText(ui.gameOverListText, Screen::k_WidthF / 2.0F, Screen::k_HeightF / 2.0F);
    }

    void DrawSplash(
        UIState& ui,
        sf::RenderWindow& window,
        const sf::Sprite& splashSprite,
        std::uint8_t alpha,
        float timeSeconds)
    {
        sf::Sprite sprite = splashSprite;
        sprite.setColor(sf::Color(255, 255, 255, alpha));
        window.draw(sprite);

        const sf::Color oldTitle = ui.splashTitleText.getFillColor();
        const sf::Color oldHint = ui.splashHintText.getFillColor();

        SetTextAlpha(ui.splashTitleText, alpha);

        const float wave = std::sin(timeSeconds * UIConfig::k_TwoPi * UIConfig::k_SplashBlinkHz);
        const float blink01 = (wave + 1.0F) * 0.5F;

        const float fade01 = static_cast<float>(alpha) / 255.0F;
        constexpr float k_MinA = 80.0F;
        constexpr float k_MaxA = 255.0F;
        const float a = (k_MinA + blink01 * (k_MaxA - k_MinA)) * fade01;

        SetTextAlpha(ui.splashHintText, static_cast<sf::Uint8>(a));

        window.draw(ui.splashTitleText);
        window.draw(ui.splashHintText);

        ui.splashTitleText.setFillColor(oldTitle);
        ui.splashHintText.setFillColor(oldHint);
    }

    void DrawMainMenu(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground)
    {
        window.draw(menuBackground);
        window.draw(ui.mainTitleText);
        window.draw(ui.playText);
        window.draw(ui.exitText);
    }

    void DrawChooseMode(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground)
    {
        window.draw(menuBackground);
        window.draw(ui.chooseTitleText);
        window.draw(ui.chooseListText);
        window.draw(ui.chooseStartText);
    }

    void DrawHud(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
    }

    void DrawGameOver(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.gameOverTitleText);
        window.draw(ui.gameOverListText);
    }
}