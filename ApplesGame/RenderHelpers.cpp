#include "RenderHelpers.h"
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    void FitSpriteToScreen(sf::Sprite& sprite, const sf::Texture& texture)
    {
        const sf::Vector2u texSize = texture.getSize();

        const float scaleX = k_ScreenWidthF / static_cast<float>(texSize.x);
        const float scaleY = k_ScreenHeightF / static_cast<float>(texSize.y);

        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(0.0F, 0.0F);
    }

    void ApplyPlayerSpriteTransform(Player& player)
    {
        const sf::Vector2f scale =
            GetSpriteScale(player.sprite, { k_PlayerSize, k_PlayerSize });

        switch (player.direction)
        {
        case EPlayerDirection::Up:
            player.sprite.setScale(scale.x, scale.y);
            player.sprite.setRotation(-90.0F);
            break;

        case EPlayerDirection::Right:
            player.sprite.setScale(scale.x, scale.y);
            player.sprite.setRotation(0.0F);
            break;

        case EPlayerDirection::Down:
            player.sprite.setScale(scale.x, scale.y);
            player.sprite.setRotation(90.0F);
            break;

        case EPlayerDirection::Left:
            player.sprite.setScale(-scale.x, scale.y);
            player.sprite.setRotation(0.0F);
            break;
        }
    }
}
