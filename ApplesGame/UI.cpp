#include "UI.h"

#include <cmath>
#include <string>

#include "Constants.h"
#include "Resources.h"

namespace ApplesGame
{
    static void ApplyBlinkToText(
        sf::Text& text,
        float& blinkTimerSeconds,
        float deltaTimeSeconds,
        float blinkPeriodSeconds = 1.0F,
        sf::Uint8 visibleAlpha = 200,
        sf::Uint8 hiddenAlpha = 40)
    {
        blinkTimerSeconds += deltaTimeSeconds;

        const float blinkPhaseTime = std::fmod(blinkTimerSeconds, blinkPeriodSeconds);

        sf::Color textColor = text.getFillColor();
        const float halfPeriodSeconds = blinkPeriodSeconds * 0.5F;
        textColor.a = (blinkPhaseTime < halfPeriodSeconds) ? visibleAlpha : hiddenAlpha;

        text.setFillColor(textColor);
    }

    static sf::Text MakeCenteredText(
        const char* string,
        const sf::Font& font,
        unsigned size,
        sf::Color color,
        float x,
        float y)
    {
        sf::Text text(string, font, size);
        text.setFillColor(color);
        SetupCenteredText(text, x, y);
        return text;
    }

    void InitUI(UIState& ui, const Resources& resources)
    {
        // HUD (Score)
        ui.scoreText.setFont(resources.fontUi);
        ui.scoreText.setCharacterSize(24);
        ui.scoreText.setFillColor(sf::Color(255, 255, 255, 160));
        ui.scoreText.setPosition(24.0F, 18.0F);

        ui.lastScore = -1;

        // Screen texts
        constexpr unsigned k_TitleSize = 45;
        constexpr unsigned k_ContinueSize = 21;
        constexpr unsigned k_GameOverSize = 36;
        constexpr unsigned k_RestartSize = 21;

        ui.menuTitleText = MakeCenteredText(
            "RABOTYAGA",
            resources.fontTitle,
            k_TitleSize,
            sf::Color::White,
            k_ScreenWidthF / 2.0F,
            k_ScreenHeightF / 2.0F - 120.0F
        );

        ui.menuContinueText = MakeCenteredText(
            "Press SPACE to continue",
            resources.fontUi,
            k_ContinueSize,
            sf::Color(200, 200, 200, 200),
            k_ScreenWidthF / 2.0F,
            k_ScreenHeightF / 2.0F - 60.0F
        );

        ui.gameOverText = MakeCenteredText(
            "GAME OVER",
            resources.fontTitle,
            k_GameOverSize,
            sf::Color::Red,
            k_ScreenWidthF / 2.0F,
            k_ScreenHeightF / 2.0F - 40.0F
        );

        ui.restartText = MakeCenteredText(
            "Press SPACE to continue",
            resources.fontUi,
            k_RestartSize,
            sf::Color(200, 200, 200, 200),
            k_ScreenWidthF / 2.0F,
            k_ScreenHeightF / 2.0F + 20.0F
        );

        ui.blinkTimerSeconds = 0.0F;
    }

    void UpdateUI(UIState& ui, const GameState& state)
    {
        // Update score text only when it changes
        if (state.score != ui.lastScore)
        {
            ui.lastScore = state.score;
            ui.scoreText.setString("Score: " + std::to_string(state.score));
        }
    }

    void DrawUI(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.scoreText);
    }

    void UpdateMenuUI(UIState& ui, float deltaTimeSeconds)
    {
        ApplyBlinkToText(ui.menuContinueText, ui.blinkTimerSeconds, deltaTimeSeconds);
    }

    void DrawMenuUI(UIState& ui, sf::RenderWindow& window, const sf::Sprite& menuBackground)
    {
        window.draw(menuBackground);
        window.draw(ui.menuTitleText);
        window.draw(ui.menuContinueText);
    }

    void UpdateGameOverUI(UIState& ui, float deltaTimeSeconds)
    {
        ApplyBlinkToText(ui.restartText, ui.blinkTimerSeconds, deltaTimeSeconds);
    }

    void DrawGameOverOverlay(UIState& ui, sf::RenderWindow& window)
    {
        window.draw(ui.gameOverText);
        window.draw(ui.restartText);
    }

    void SetupCenteredText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(
            bounds.left + bounds.width / 2.0F,
            bounds.top + bounds.height / 2.0F
        );
        text.setPosition(x, y);
    }
}
