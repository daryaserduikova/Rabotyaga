#include "UI.h"

namespace ApplesGame
{
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

    void DrawGameOver(UIState& ui, sf::RenderWindow& window, const sf::Sprite& background)
    {
        window.draw(background);
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