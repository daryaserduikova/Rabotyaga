#include "Resources.h"

#include "Constants.h"
#include "Logger.h"

namespace ApplesGame
{
    bool Resources::LoadTexture(sf::Texture& t, const std::string& path)
    {
        if (!t.loadFromFile(path))
        {
            LogError("Failed to load texture: " + path);
            return false;
        }
        return true;
    }

    bool Resources::LoadFont(sf::Font& f, const std::string& path)
    {
        if (!f.loadFromFile(path))
        {
            LogError("Failed to load font: " + path);
            return false;
        }
        return true;
    }

    bool Resources::Load(const std::string& basePath)
    {
        bool ok = true;

        ok = LoadTexture(m_playerTexture, basePath + "Player.png") && ok;
        ok = LoadTexture(m_appleTexture, basePath + "Apple.png") && ok;

        ok = LoadTexture(m_backgroundTexture, basePath + "Background.png") && ok;
        ok = LoadTexture(m_menuBackgroundTexture, basePath + "MenuBackground.png") && ok;

        ok = LoadFont(m_fontUi, basePath + k_FontPath) && ok;
        ok = LoadFont(m_fontTitle, basePath + "Fonts/ContraPhobotech.otf") && ok;

        return ok;
    }
}
