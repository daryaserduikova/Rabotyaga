#include "Player.h"

namespace ApplesGame
{
    void Player::Reset(const sf::Texture& texture)
    {
        m_position = { Screen::WidthF / 2.0F, Screen::HeightF / 2.0F };
        m_speed = PlayerConfig::InitialSpeed;
        m_direction = EPlayerDirection::Right;

        m_sprite.setTexture(texture);
        m_sprite.setOrigin(GetSpriteOrigin(m_sprite, { 0.5F, 0.5F }));
        m_sprite.setScale(GetSpriteScale(m_sprite, { PlayerConfig::Size, PlayerConfig::Size }));
        m_sprite.setRotation(0.0F);
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

        if (right) m_direction = EPlayerDirection::Right;
        else if (up) m_direction = EPlayerDirection::Up;
        else if (left) m_direction = EPlayerDirection::Left;
        else if (down) m_direction = EPlayerDirection::Down;
    }

    void Player::Update(float dt)
    {
        switch (m_direction)
        {
        case EPlayerDirection::Up:    m_position.y -= m_speed * dt; break;
        case EPlayerDirection::Right: m_position.x += m_speed * dt; break;
        case EPlayerDirection::Down:  m_position.y += m_speed * dt; break;
        case EPlayerDirection::Left:  m_position.x -= m_speed * dt; break;
        }
    }

    void Player::ApplySpriteTransform()
    {
        const sf::Vector2f scale = GetSpriteScale(m_sprite, { PlayerConfig::Size, PlayerConfig::Size });

        switch (m_direction)
        {
        case EPlayerDirection::Up:
            m_sprite.setScale(scale.x, scale.y);
            m_sprite.setRotation(-90.0F);
            break;

        case EPlayerDirection::Right:
            m_sprite.setScale(scale.x, scale.y);
            m_sprite.setRotation(0.0F);
            break;

        case EPlayerDirection::Down:
            m_sprite.setScale(scale.x, scale.y);
            m_sprite.setRotation(90.0F);
            break;

        case EPlayerDirection::Left:
            m_sprite.setScale(-scale.x, scale.y);
            m_sprite.setRotation(0.0F);
            break;
        }
    }

    void Player::Draw(sf::RenderWindow& window)
    {
        m_sprite.setPosition(OurVectorToSf(m_position));
        ApplySpriteTransform();
        window.draw(m_sprite);
    }

    bool Player::HasCollisionWithScreenBorder() const
    {
        return (m_position.x - PlayerConfig::Radius < 0.0F) ||
            (m_position.x + PlayerConfig::Radius > Screen::WidthF) ||
            (m_position.y - PlayerConfig::Radius < 0.0F) ||
            (m_position.y + PlayerConfig::Radius > Screen::HeightF);
    }

    void Player::AddSpeed(float delta)
    {
        m_speed += delta;
        if (m_speed < 0.0F) m_speed = 0.0F;
    }
}
