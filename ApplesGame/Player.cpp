#include "Player.h"
#include "Math.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const sf::Texture& texture)
    {
        player.position =
        {
            k_ScreenWidthF / 2.0F,
            k_ScreenHeightF / 2.0F
        };

        player.speed = k_InitialSpeed;
        player.direction = EPlayerDirection::Right;

        player.sprite.setTexture(texture);
        player.sprite.setOrigin(GetSpriteOrigin(player.sprite, { 0.5F, 0.5F }));
        player.sprite.setScale(GetSpriteScale(player.sprite, { k_PlayerSize, k_PlayerSize }));
        player.sprite.setRotation(0.0F);
    }

    void UpdatePlayer(Player& player, float deltaTimeSeconds)
    {
        switch (player.direction)
        {
        case EPlayerDirection::Up:
            player.position.y -= player.speed * deltaTimeSeconds;
            break;

        case EPlayerDirection::Right:
            player.position.x += player.speed * deltaTimeSeconds;
            break;

        case EPlayerDirection::Down:
            player.position.y += player.speed * deltaTimeSeconds;
            break;

        case EPlayerDirection::Left:
            player.position.x -= player.speed * deltaTimeSeconds;
            break;
        }
    }

    bool HasPlayerCollisionWithScreenBorder(const Player& player)
    {
        return (player.position.x - k_PlayerRadius < 0.0F) ||
            (player.position.x + k_PlayerRadius > k_ScreenWidthF) ||
            (player.position.y - k_PlayerRadius < 0.0F) ||
            (player.position.y + k_PlayerRadius > k_ScreenHeightF);
    }
}
