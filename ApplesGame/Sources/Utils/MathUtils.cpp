#include "MathUtils.h"
#include <cmath>
#include <cstdlib>

namespace ApplesGame
{
    Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
    {
        return
        {
            (std::rand() / static_cast<float>(RAND_MAX)) * screenWidth,
            (std::rand() / static_cast<float>(RAND_MAX)) * screenHeight
        };
    }

    bool IsCirclesCollide(Position2D p1, float r1, Position2D p2, float r2)
    {
        const float dx = p1.x - p2.x;
        const float dy = p1.y - p2.y;
        const float distSquared = dx * dx + dy * dy;
        const float radiusSum = r1 + r2;
        return distSquared <= (radiusSum * radiusSum);
    }

    sf::Vector2f OurVectorToSf(const Vector2D& v)
    {
        return { v.x, v.y };
    }

    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize)
    {
        const sf::Texture* texture = sprite.getTexture();
        if (!texture)
            return { 1.0F, 1.0F };

        const sf::Vector2u textureSize = texture->getSize();
        return
        {
            desiredSize.x / static_cast<float>(textureSize.x),
            desiredSize.y / static_cast<float>(textureSize.y)
        };
    }

    sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition)
    {
        const sf::Texture* texture = sprite.getTexture();
        if (!texture)
            return { 0.0F, 0.0F };

        const sf::Vector2u textureSize = texture->getSize();
        return
        {
            relativePosition.x * static_cast<float>(textureSize.x),
            relativePosition.y * static_cast<float>(textureSize.y)
        };
    }

    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        return
        {
            (bounds.left + bounds.width) * relativePosition.x,
            (bounds.top + bounds.height) * relativePosition.y
        };
    }

    float Clamp(float value, float minValue, float maxValue)
    {
        if (value < minValue)
            return minValue;

        if (value > maxValue)
            return maxValue;

        return value;
    }
}