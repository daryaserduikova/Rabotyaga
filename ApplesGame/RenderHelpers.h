#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

namespace ApplesGame
{
    void FitSpriteToScreen(sf::Sprite& sprite, const sf::Texture& texture);
    void ApplyPlayerSpriteTransform(Player& player);
}
