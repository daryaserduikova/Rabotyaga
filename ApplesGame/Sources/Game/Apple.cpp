// @file Apple.cpp

#include "Apple.h"

namespace ApplesGame
{
    void Apple::Respawn(const sf::Texture& texture)
    {
        m_Position = GetRandomPositionInScreen(Screen::k_WidthF, Screen::k_HeightF);

        m_Position.x = Clamp(
            m_Position.x,
            AppleConfig::k_Radius,
            Screen::k_WidthF - AppleConfig::k_Radius
        );

        m_Position.y = Clamp(
            m_Position.y,
            AppleConfig::k_Radius,
            Screen::k_HeightF - AppleConfig::k_Radius
        );

        m_Sprite.setTexture(texture);
        m_Sprite.setOrigin(GetSpriteOrigin(m_Sprite, { 0.5F, 0.5F }));
        m_Sprite.setScale(GetSpriteScale(m_Sprite, { AppleConfig::k_Size, AppleConfig::k_Size }));
        m_Sprite.setRotation(0.0F);
    }

    void Apple::Draw(sf::RenderWindow& window)
    {
        m_Sprite.setPosition(OurVectorToSf(m_Position));
        window.draw(m_Sprite);
    }
}