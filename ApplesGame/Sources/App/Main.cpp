// @file main.cpp

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "Game.h"

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(ApplesGame::Screen::k_Width, ApplesGame::Screen::k_Height),
        "RABOTYAGA"
    );
    window.setFramerateLimit(60);

    ApplesGame::Game game;
    if (!game.Init())
    {
        return 1;
    }

    sf::Clock clock;
    float prevSeconds = clock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        const float nowSeconds = clock.getElapsedTime().asSeconds();
        float dtSeconds = nowSeconds - prevSeconds;
        prevSeconds = nowSeconds;

        if (dtSeconds > ApplesGame::Screen::k_MaxDtSeconds)
        {
            dtSeconds = ApplesGame::Screen::k_MaxDtSeconds;
        }

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game.Shutdown();
                window.close();
                break;
            }

            game.HandleEvent(event);
        }

        if (game.ShouldExit())
        {
            game.Shutdown();
            window.close();
            break;
        }

        game.Update(dtSeconds);

        window.clear();
        game.Draw(window);
        window.display();
    }

    return 0;
}
