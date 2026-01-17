#include "Apple.h"

#include <algorithm>

namespace ApplesGame
{
    void Apple::Respawn(const sf::Texture& texture)
    {
        m_position = GetRandomPositionInScreen(k_ScreenWidthF, k_ScreenHeightF);

        m_position.x = std::max(k_AppleRadius, std::min(m_position.x, k_ScreenWidthF - k_AppleRadius));
        m_position.y = std::max(k_AppleRadius, std::min(m_position.y, k_ScreenHeightF - k_AppleRadius));

        m_sprite.setTexture(texture);
        m_sprite.setOrigin(GetSpriteOrigin(m_sprite, { 0.5F, 0.5F }));
        m_sprite.setScale(GetSpriteScale(m_sprite, { k_AppleSize, k_AppleSize }));
        m_sprite.setRotation(0.0F);
    }

    void Apple::Draw(sf::RenderWindow& window)
    {
        m_sprite.setPosition(OurVectorToSf(m_position));
        window.draw(m_sprite);
    }
}
