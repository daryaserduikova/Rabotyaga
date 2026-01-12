#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Constants.h"

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(ApplesGame::k_ScreenWidth, ApplesGame::k_ScreenHeight),
        "RABOTYAGA"
    );
    window.setFramerateLimit(60);

    ApplesGame::Game game;
    if (!ApplesGame::InitGame(game))
    {
        return 1;
    }

    sf::Clock clock;

    float previousTimeSeconds = clock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        const float currentTimeSeconds = clock.getElapsedTime().asSeconds();
        float deltaTimeSeconds = currentTimeSeconds - previousTimeSeconds;
        previousTimeSeconds = currentTimeSeconds;

        if (deltaTimeSeconds > ApplesGame::k_MaxDtSeconds)
        {
            deltaTimeSeconds = ApplesGame::k_MaxDtSeconds;
        }

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space)
            {
                if (game.state.mode == ApplesGame::EGameMode::MainMenu ||
                    game.state.mode == ApplesGame::EGameMode::GameOver)
                {
                    ApplesGame::ResetGameplay(game);
                    game.state.mode = ApplesGame::EGameMode::Playing;
                }
            }
        }

        ApplesGame::UpdateGame(game, deltaTimeSeconds);

        window.clear();
        ApplesGame::DrawGame(game, window);
        window.display();
    }

    return 0;
}
