#include "Apple.h"
#include <algorithm>

namespace ApplesGame
{
    void Apple::Respawn(const sf::Texture& texture)
    {
        m_position = GetRandomPositionInScreen(Screen::WidthF, Screen::HeightF);

        m_position.x = std::max(AppleConfig::Radius, std::min(m_position.x, Screen::WidthF - AppleConfig::Radius));
        m_position.y = std::max(AppleConfig::Radius, std::min(m_position.y, Screen::HeightF - AppleConfig::Radius));

        m_sprite.setTexture(texture);
        m_sprite.setOrigin(GetSpriteOrigin(m_sprite, { 0.5F, 0.5F }));
        m_sprite.setScale(GetSpriteScale(m_sprite, { AppleConfig::Size, AppleConfig::Size }));
        m_sprite.setRotation(0.0F);
    }

    void Apple::Draw(sf::RenderWindow& window)
    {
        m_sprite.setPosition(OurVectorToSf(m_position));
        window.draw(m_sprite);
    }
}
