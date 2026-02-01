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
        text.setOrigin(bounds.left + bounds.width / 2.0F, bounds.top + bounds.height / 2.0F);
        text.setPosition(x, y);
    }

    static sf::Text MakeCenteredText(
        const char* str,
        const sf::Font& font,
        unsigned size,
        sf::Color color,
        float x,
        float y)
    {
        sf::Text text(str, font, size);
        text.setFillColor(color);
        SetupCenteredText(text, x, y);
        return text;
    }

    static const char* Arrow(bool isActive)
    {
        if (isActive)
        {
            return "> ";
        }

        return "  ";
    }

    static const char* Check(bool isActive)
    {
        if (isActive)
        {
            return "[X] ";
        }

        return "[ ] ";
    }

    static void SetTextAlpha(sf::Text& text, sf::Uint8 alpha)
    {
        sf::Color c = text.getFillColor();
        c.a = alpha;
        text.setFillColor(c);
    }

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont)
    {
        ui.scoreText.setFont(uiFont);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(sf::Color(255, 255, 255, 160));
        ui.scoreText.setPosition(24.0F, 18.0F);
        ui.lastScore = -1;

        // Splash
        ui.splashTitleText = MakeCenteredText(
            "RABOTYAGA",
            titleFont,
            54,
            sf::Color::White,
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

        // Main menu
        ui.mainTitleText = MakeCenteredText(
            "RABOTYAGA",
            titleFont,
            48,
            sf::Color::White,
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F - 90.0F
        );

        ui.playText.setFont(uiFont);
        ui.playText.setCharacterSize(28);
        ui.playText.setFillColor(sf::Color(255, 255, 255, 230));

        ui.exitText = ui.playText;

        // Choose mode
        ui.chooseTitleText = MakeCenteredText(
            "CHOOSE MODE",
            titleFont,
            36,
            sf::Color::White,
            Screen::k_WidthF / 2.0F,
            120.0F
        );

        ui.chooseListText.setFont(uiFont);
        ui.chooseListText.setCharacterSize(18);
        ui.chooseListText.setFillColor(sf::Color(255, 255, 255, 220));

        // Game over
        ui.gameOverTitleText = MakeCenteredText(
            "GAME OVER",
            titleFont,
            36,
            sf::Color::Red,
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F - 90.0F
        );

        ui.gameOverListText.setFont(uiFont);
        ui.gameOverListText.setCharacterSize(22);
        ui.gameOverListText.setFillColor(sf::Color(255, 255, 255, 230));
    }

    void UpdateUI(UIState& ui, const UIModel& model)
    {
        if (model.score != ui.lastScore)
        {
            ui.lastScore = model.score;
            ui.scoreText.setString("Score: " + std::to_string(model.score));
        }

        // Main menu
        ui.playText.setString(model.mainMenuIndex == 0 ? "> Play" : "  Play");
        ui.exitText.setString(model.mainMenuIndex == 1 ? "> Exit" : "  Exit");
        ui.playText.setPosition(Screen::k_WidthF / 2.0F - 60.0F, 260.0F);
        ui.exitText.setPosition(Screen::k_WidthF / 2.0F - 60.0F, 305.0F);

        // Choose mode
        const bool finite20 = HasRule(model.rules, EGameRule::Finite20);
        const bool finite50 = HasRule(model.rules, EGameRule::Finite50);
        const bool infinite = HasRule(model.rules, EGameRule::InfiniteApples);

        const bool speedUp = HasRule(model.rules, EGameRule::SpeedUpOnEat);
        const bool noSpeed = HasRule(model.rules, EGameRule::NoSpeedUpOnEat);

        std::string s;
        s += "Apples:\n";
        s += std::string(Arrow(model.chooseIndex == 0)) + Check(finite20) + "1 - Finite (20)\n";
        s += std::string(Arrow(model.chooseIndex == 1)) + Check(finite50) + "2 - Finite (50)\n";
        s += std::string(Arrow(model.chooseIndex == 2)) + Check(infinite) + "3 - Infinite\n\n";

        s += "Speed:\n";
        s += std::string(Arrow(model.chooseIndex == 3)) + Check(speedUp) + "4 - Speed up on eat\n";
        s += std::string(Arrow(model.chooseIndex == 4)) + Check(noSpeed) + "5 - No speed up\n\n";

        s += std::string(Arrow(model.chooseIndex == 5)) + "START\n";

        ui.chooseListText.setString(s.c_str());
        ui.chooseListText.setPosition(60.0F, 180.0F);

        // Game over
        std::string g;
        g += std::string(Arrow(model.gameOverIndex == 0)) + "Restart\n";
        g += std::string(Arrow(model.gameOverIndex == 1)) + "Exit\n";

        ui.gameOverListText.setString(g.c_str());
        SetupCenteredText(
            ui.gameOverListText,
            Screen::k_WidthF / 2.0F,
            Screen::k_HeightF / 2.0F
        );
    }

    void DrawSplash(
        UIState& ui,
        sf::RenderWindow& window,
        const sf::Sprite& splashSprite,
        std::uint8_t alpha,
        float timeSeconds)
    {
        sf::Sprite sprite = splashSprite;
        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
        window.draw(sprite);

        const sf::Color oldTitle = ui.splashTitleText.getFillColor();
        const sf::Color oldHint = ui.splashHintText.getFillColor();

        SetTextAlpha(ui.splashTitleText, static_cast<std::uint8_t>(alpha));

        {
            constexpr float k_BlinkHz = 1.5F;
            constexpr float k_TwoPi = 6.28318530718F;

            const float wave = std::sin(timeSeconds * k_TwoPi * k_BlinkHz);
            const float blink01 = (wave + 1.0F) * 0.5F;

            const float combined = blink01 * (static_cast<float>(alpha) / 255.0F);
            const std::uint8_t hintAlpha = static_cast<std::uint8_t>(combined * 255.0F);

            SetTextAlpha(ui.splashHintText, hintAlpha);
        }

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
