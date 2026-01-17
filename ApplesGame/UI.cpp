#include "UI.h"

#include <cmath>
#include <string>

#include "Constants.h"

namespace ApplesGame
{
    static void ApplyBlinkToText(
        sf::Text& text,
        float& blinkTimerSeconds,
        float dt,
        float period = 1.0F,
        sf::Uint8 visibleAlpha = 200,
        sf::Uint8 hiddenAlpha = 40)
    {
        blinkTimerSeconds += dt;
        const float phase = std::fmod(blinkTimerSeconds, period);

        sf::Color c = text.getFillColor();
        c.a = (phase < period * 0.5F) ? visibleAlpha : hiddenAlpha;
        text.setFillColor(c);
    }

    void SetupCenteredText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect b = text.getLocalBounds();
        text.setOrigin(b.left + b.width / 2.0F, b.top + b.height / 2.0F);
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
        sf::Text t(str, font, size);
        t.setFillColor(color);
        SetupCenteredText(t, x, y);
        return t;
    }

    void InitUI(UIState& ui, const sf::Font& uiFont, const sf::Font& titleFont)
    {
        ui.scoreText.setFont(uiFont);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(sf::Color(255, 255, 255, 160));
        ui.scoreText.setPosition(24.0F, 18.0F);

        ui.lastScore = -1;

        constexpr unsigned k_TitleSize = 45;
        constexpr unsigned k_ContinueSize = 21;
        constexpr unsigned k_GameOverSize = 36;
        constexpr unsigned k_RestartSize = 21;

        ui.menuTitleText = MakeCenteredText(
            "RABOTYAGA",
            titleFont,
            k_TitleSize,
            sf::Color::White,
            Screen::WidthF / 2.0F,
            Screen::HeightF / 2.0F - 120.0F
        );

        ui.menuContinueText = MakeCenteredText(
            "Press SPACE to continue",
            uiFont,
            k_ContinueSize,
            sf::Color(200, 200, 200, 200),
            Screen::WidthF / 2.0F,
            Screen::HeightF / 2.0F - 60.0F
        );

        ui.gameOverText = MakeCenteredText(
            "GAME OVER",
            titleFont,
            k_GameOverSize,
            sf::Color::Red,
            Screen::WidthF / 2.0F,
            Screen::HeightF / 2.0F - 40.0F
        );

        ui.restartText = MakeCenteredText(
            "Press SPACE to continue",
            uiFont,
            k_RestartSize,
            sf::Color(200, 200, 200, 200),
            Screen::WidthF / 2.0F,
            Screen::HeightF / 2.0F + 20.0F
        );

        ui.blinkTimerSeconds = 0.0F;
    }

    void UpdateUI(UIState& ui, const UIModel& model)
    {
        (void)model.mode;

        if (model.score != ui.lastScore)
        {
            ui.lastScore = model.score;
            ui.scoreText.setString("Score: " + std::to_string(model.score));
        }
    }

    void DrawUI(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
    }

    void UpdateMenuUI(UIState& ui, float dt)
    {
        ApplyBlinkToText(ui.menuContinueText, ui.blinkTimerSeconds, dt);
    }

    void DrawMenuUI(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground)
    {
        window.draw(menuBackground);
        window.draw(ui.menuTitleText);
        window.draw(ui.menuContinueText);
    }

    void UpdateGameOverUI(UIState& ui, float dt)
    {
        ApplyBlinkToText(ui.restartText, ui.blinkTimerSeconds, dt);
    }

    void DrawGameOverOverlay(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.gameOverText);
        window.draw(ui.restartText);
    }
}
