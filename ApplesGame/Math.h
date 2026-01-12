#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0.0F;
        float y = 0.0F;
    };

    using Position2D = Vector2D;

    Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

    bool IsCirclesCollide(Position2D p1, float r1, Position2D p2, float r2);

    sf::Vector2f OurVectorToSf(const Vector2D& v);
    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize);
    sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition);
    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
}