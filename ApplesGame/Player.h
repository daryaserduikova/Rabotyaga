#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    enum class EPlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Position2D position;
        float speed = k_InitialSpeed;
        EPlayerDirection direction = EPlayerDirection::Right;
        sf::Sprite sprite;
    };

    void InitPlayer(Player& player, const sf::Texture& texture);
    void UpdatePlayer(Player& player, float deltaTimeSeconds);

    bool HasPlayerCollisionWithScreenBorder(const Player& player);
}
