#include "Apple.h"

#include <algorithm>

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    void InitApple(Apple& apple, const sf::Texture& texture)
    {
        apple.position = GetRandomPositionInScreen(k_ScreenWidthF, k_ScreenHeightF);

        apple.position.x = std::max(
            k_AppleRadius,
            std::min(apple.position.x, k_ScreenWidthF - k_AppleRadius)
        );

        apple.position.y = std::max(
            k_AppleRadius,
            std::min(apple.position.y, k_ScreenHeightF - k_AppleRadius)
        );

        apple.sprite.setTexture(texture);
        apple.sprite.setOrigin(GetSpriteOrigin(apple.sprite, { 0.5F, 0.5F }));
        apple.sprite.setScale(GetSpriteScale(apple.sprite, { k_AppleSize, k_AppleSize }));
        apple.sprite.setRotation(0.0F);
    }

    void DrawApple(Apple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(OurVectorToSf(apple.position));
        window.draw(apple.sprite);
    }
}
