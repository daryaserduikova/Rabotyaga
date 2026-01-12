#include "Math.h"
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
        if (texture == nullptr)
        {
            return { 1.0F, 1.0F };
        }

        const sf::Vector2u textureSize = texture->getSize();
        return { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
    }

    sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition)
    {
        const sf::Texture* texture = sprite.getTexture();
        if (texture == nullptr)
        {
            return { 0.0F, 0.0F };
        }

        const sf::Vector2u textureSize = texture->getSize();
        return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
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
}
