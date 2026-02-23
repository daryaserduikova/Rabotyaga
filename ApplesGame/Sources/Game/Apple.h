// @file Apple.h

#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "MathUtils.h"

namespace ApplesGame
{
    class Apple
    {
    public:
        void Respawn(const sf::Texture& texture);
        void Draw(sf::RenderWindow& window);

        const Position2D& Position() const { return m_Position; }
        float Radius() const { return AppleConfig::k_Radius; }

    private:
        Position2D m_Position{};
        sf::Sprite m_Sprite;
    };
}
