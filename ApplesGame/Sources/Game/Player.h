#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "MathUtils.h"

namespace ApplesGame
{
    enum class EPlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    class Player
    {
    public:
        void Reset(const sf::Texture& texture);

        void Update(float dtSeconds);
        void Draw(sf::RenderWindow& window);

        void SetDirection(EPlayerDirection dir);

        bool HasCollisionWithScreenBorder() const;

        const Position2D& Position() const { return m_Position; }
        float Radius() const { return PlayerConfig::k_Radius; }

        void AddSpeed(float delta);

    private:
        void ApplySpriteTransform();

        Position2D m_Position{};
        float m_Speed = PlayerConfig::k_InitialSpeed;
        EPlayerDirection m_Direction = EPlayerDirection::Right;
        sf::Sprite m_Sprite;
    };
}