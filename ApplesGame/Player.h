#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    enum class EPlayerDirection { Right = 0, Up, Left, Down };

    class Player
    {
    public:
        void Reset(const sf::Texture& texture);

        void HandleInput();
        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        bool HasCollisionWithScreenBorder() const;

        const Position2D& Position() const { return m_position; }
        float Radius() const { return PlayerConfig::Radius; }

        void AddSpeed(float delta);

    private:
        void ApplySpriteTransform();

        Position2D m_position{};
        float m_speed = PlayerConfig::InitialSpeed;
        EPlayerDirection m_direction = EPlayerDirection::Right;
        sf::Sprite m_sprite;
    };
}
