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

        const Position2D& Position() const { return m_position; }
        float Radius() const { return AppleConfig::Radius; }

    private:
        Position2D m_position{};
        sf::Sprite m_sprite;
    };
}
