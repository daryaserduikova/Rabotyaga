#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    class Apple
    {
    public:
        void Respawn(const sf::Texture& texture);
        void Draw(sf::RenderWindow& window);

        const Position2D& GetPosition() const { return m_position; }
        float GetRadius() const { return k_AppleRadius; }

    private:
        Position2D m_position{};
        sf::Sprite m_sprite;
    };
}
