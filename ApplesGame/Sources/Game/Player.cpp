// @file Player.cpp

#include "Player.h"

namespace ApplesGame
{
    void Player::Reset(const sf::Texture& texture)
    {
        m_Position = { Screen::k_WidthF / 2.0F, Screen::k_HeightF / 2.0F };
        m_Speed = PlayerConfig::k_InitialSpeed;
        m_Direction = EPlayerDirection::Right;

        m_Sprite.setTexture(texture);
        m_Sprite.setOrigin(GetSpriteOrigin(m_Sprite, { 0.5F, 0.5F }));
        m_Sprite.setScale(GetSpriteScale(m_Sprite, { PlayerConfig::k_Size, PlayerConfig::k_Size }));
        m_Sprite.setRotation(0.0F);
    }

    void Player::HandleInput()
    {
        const bool right =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        const bool up =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        const bool left =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A);

        const bool down =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S);

        if (right)
        {
            m_Direction = EPlayerDirection::Right;
        }
        else if (up)
        {
            m_Direction = EPlayerDirection::Up;
        }
        else if (left)
        {
            m_Direction = EPlayerDirection::Left;
        }
        else if (down)
        {
            m_Direction = EPlayerDirection::Down;
        }
    }

    void Player::Update(float dtSeconds)
    {
        switch (m_Direction)
        {
        case EPlayerDirection::Up:
        {
            m_Position.y -= m_Speed * dtSeconds;
            break;
        }
        case EPlayerDirection::Right:
        {
            m_Position.x += m_Speed * dtSeconds;
            break;
        }
        case EPlayerDirection::Down:
        {
            m_Position.y += m_Speed * dtSeconds;
            break;
        }
        case EPlayerDirection::Left:
        {
            m_Position.x -= m_Speed * dtSeconds;
            break;
        }
        }
    }

    void Player::ApplySpriteTransform()
    {
        const sf::Vector2f scale = GetSpriteScale(m_Sprite, { PlayerConfig::k_Size, PlayerConfig::k_Size });

        switch (m_Direction)
        {
        case EPlayerDirection::Up:
        {
            m_Sprite.setScale(scale.x, scale.y);
            m_Sprite.setRotation(-90.0F);
            break;
        }
        case EPlayerDirection::Right:
        {
            m_Sprite.setScale(scale.x, scale.y);
            m_Sprite.setRotation(0.0F);
            break;
        }
        case EPlayerDirection::Down:
        {
            m_Sprite.setScale(scale.x, scale.y);
            m_Sprite.setRotation(90.0F);
            break;
        }
        case EPlayerDirection::Left:
        {
            m_Sprite.setScale(-scale.x, scale.y);
            m_Sprite.setRotation(0.0F);
            break;
        }
        }
    }

    void Player::Draw(sf::RenderWindow& window)
    {
        m_Sprite.setPosition(OurVectorToSf(m_Position));
        ApplySpriteTransform();
        window.draw(m_Sprite);
    }

    bool Player::HasCollisionWithScreenBorder() const
    {
        if (m_Position.x - PlayerConfig::k_Radius < 0.0F)
        {
            return true;
        }

        if (m_Position.x + PlayerConfig::k_Radius > Screen::k_WidthF)
        {
            return true;
        }

        if (m_Position.y - PlayerConfig::k_Radius < 0.0F)
        {
            return true;
        }

        if (m_Position.y + PlayerConfig::k_Radius > Screen::k_HeightF)
        {
            return true;
        }

        return false;
    }

    void Player::AddSpeed(float delta)
    {
        m_Speed += delta;

        if (m_Speed < 0.0F)
        {
            m_Speed = 0.0F;
        }
    }
}
