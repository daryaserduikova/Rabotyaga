#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
    class Resources
    {
    public:
        bool Load(const std::string& basePath);

        // Textures
        const sf::Texture& PlayerTexture() const { return m_playerTexture; }
        const sf::Texture& AppleTexture() const { return m_appleTexture; }
        const sf::Texture& BackgroundTexture() const { return m_backgroundTexture; }
        const sf::Texture& MenuBackgroundTexture() const { return m_menuBackgroundTexture; }

        // Fonts
        const sf::Font& UiFont() const { return m_fontUi; }
        const sf::Font& TitleFont() const { return m_fontTitle; }

    private:
        bool LoadTexture(sf::Texture& texture, const std::string& path);
        bool LoadFont(sf::Font& font, const std::string& path);

        sf::Texture m_playerTexture;
        sf::Texture m_appleTexture;

        sf::Texture m_backgroundTexture;
        sf::Texture m_menuBackgroundTexture;

        sf::Font m_fontUi;
        sf::Font m_fontTitle;
    };
}
