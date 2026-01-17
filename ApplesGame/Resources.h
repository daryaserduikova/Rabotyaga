#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame
{
    class Resources
    {
    public:
        bool Load(const std::string& basePath);

        const sf::Texture& GetPlayerTexture() const { return m_playerTexture; }
        const sf::Texture& GetAppleTexture() const { return m_appleTexture; }
        const sf::Texture& GetBackgroundTexture() const { return m_backgroundTexture; }
        const sf::Texture& GetMenuBackgroundTexture() const { return m_menuBackgroundTexture; }

        const sf::Font& GetUiFont() const { return m_fontUi; }
        const sf::Font& GetTitleFont() const { return m_fontTitle; }

    private:
        bool LoadTexture(sf::Texture& t, const std::string& path);
        bool LoadFont(sf::Font& f, const std::string& path);

        sf::Texture m_playerTexture;
        sf::Texture m_appleTexture;

        sf::Texture m_backgroundTexture;
        sf::Texture m_menuBackgroundTexture;

        sf::Font m_fontUi;
        sf::Font m_fontTitle;
    };
}
