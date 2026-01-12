#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Resources
    {
        sf::Texture playerTexture;
        sf::Texture appleTexture;

        sf::Texture backgroundTexture;
        sf::Texture menuBackgroundTexture;

        sf::Font fontUi;
        sf::Font fontTitle;
    };

    bool LoadResources(Resources& resources);
}
