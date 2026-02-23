// @file Resources.h

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
    class Resources
    {
    public:
        bool Load(const std::string& basePath);

        const sf::Texture& PlayerTexture() const { return m_PlayerTexture; }
        const sf::Texture& AppleTexture() const { return m_AppleTexture; }
        const sf::Texture& BackgroundTexture() const { return m_BackgroundTexture; }

        const sf::Texture& MenuBackgroundTexture() const { return m_MenuBackgroundTexture; }
        const sf::Texture& ChooseMenuBackgroundTexture() const { return m_ChooseMenuBackgroundTexture; }

        const sf::Texture& SplashTexture() const { return m_SplashTexture; }

        const sf::Font& UiFont() const { return m_UiFont; }
        const sf::Font& TitleFont() const { return m_TitleFont; }

    private:
        static bool LoadTexture(sf::Texture& texture, const std::string& path);
        static bool LoadFont(sf::Font& font, const std::string& path);

        sf::Texture m_PlayerTexture;
        sf::Texture m_AppleTexture;

        sf::Texture m_BackgroundTexture;

        sf::Texture m_MenuBackgroundTexture;
        sf::Texture m_ChooseMenuBackgroundTexture;

        sf::Texture m_SplashTexture;

        sf::Font m_UiFont;
        sf::Font m_TitleFont;
    };
}