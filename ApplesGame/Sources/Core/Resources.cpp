// @file Resources.cpp

#include "Resources.h"

#include "Constants.h"
#include "Loggers.h"

namespace ApplesGame
{
    bool Resources::LoadTexture(sf::Texture& texture, const std::string& path)
    {
        if (!texture.loadFromFile(path))
        {
            LogError("Failed to load texture: " + path);
            return false;
        }

        return true;
    }

    bool Resources::LoadFont(sf::Font& font, const std::string& path)
    {
        if (!font.loadFromFile(path))
        {
            LogError("Failed to load font: " + path);
            return false;
        }

        return true;
    }

    bool Resources::Load(const std::string& basePath)
    {
        bool ok = true;

        ok = LoadTexture(m_PlayerTexture, basePath + "Player.png") && ok;
        ok = LoadTexture(m_AppleTexture, basePath + "Apple.png") && ok;

        ok = LoadTexture(m_BackgroundTexture, basePath + "Background.png") && ok;

        ok = LoadTexture(m_MenuBackgroundTexture, basePath + "MenuBackground.png") && ok;
        ok = LoadTexture(m_ChooseMenuBackgroundTexture, basePath + "MenuChooseMode.png") && ok;

        ok = LoadTexture(m_SplashTexture, basePath + "Splash.png") && ok;

        ok = LoadFont(m_UiFont, basePath + Paths::k_UiFont) && ok;
        ok = LoadFont(m_TitleFont, basePath + Paths::k_TitleFont) && ok;

        return ok;
    }
}