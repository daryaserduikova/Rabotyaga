#include "RenderHelpers.h"
#include "Constants.h"

namespace ApplesGame
{
    void FitSpriteToScreen(sf::Sprite& sprite, const sf::Texture& texture)
    {
        const sf::Vector2u texSize = texture.getSize();

        const float scaleX = Screen::WidthF / static_cast<float>(texSize.x);
        const float scaleY = Screen::HeightF / static_cast<float>(texSize.y);

        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0.0F, 0.0F);
    }
}
