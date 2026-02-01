#include "RenderHelpers.h"
#include "Constants.h"

namespace ApplesGame
{
    void FitSpriteToScreen(sf::Sprite& sprite)
    {
        const sf::Texture* texture = sprite.getTexture();
        if (texture == nullptr)
        {
            return;
        }

        const sf::Vector2u texSize = texture->getSize();
        if (texSize.x == 0U || texSize.y == 0U)
        {
            return;
        }

        const float scaleX = Screen::k_WidthF / static_cast<float>(texSize.x);
        const float scaleY = Screen::k_HeightF / static_cast<float>(texSize.y);

        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0.0F, 0.0F);
    }
}
