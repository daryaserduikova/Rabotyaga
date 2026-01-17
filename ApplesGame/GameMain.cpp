#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "Game.h"

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(ApplesGame::k_ScreenWidth, ApplesGame::k_ScreenHeight),
        "RABOTYAGA"
    );
    window.setFramerateLimit(60);

    ApplesGame::Game game;
    if (!game.Init())
    {
        return 1;
    }

    sf::Clock clock;
    float previousTimeSeconds = clock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTimeSeconds = clock.getElapsedTime().asSeconds();
        float dt = currentTimeSeconds - previousTimeSeconds;
        previousTimeSeconds = currentTimeSeconds;

        if (dt > ApplesGame::k_MaxDtSeconds)
        {
            dt = ApplesGame::k_MaxDtSeconds;
        }

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                game.Shutdown();
                window.close();
                break;
            }

            game.HandleEvent(event);
        }

        game.Update(dt);

        window.clear();
        game.Draw(window);
        window.display();
    }

    return 0;
}
