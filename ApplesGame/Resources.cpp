#include "Resources.h"
#include "Constants.h"
#include <string>

namespace ApplesGame
{
    bool LoadResources(Resources& r)
    {
        const std::string base = k_ResourcesPath;

        if (!r.playerTexture.loadFromFile(base + "Player.png"))
        {
            return false;
        }

        if (!r.appleTexture.loadFromFile(base + "Apple.png")) 
        {
            return false;
        }

        if (!r.backgroundTexture.loadFromFile(base + "Background.png")) 
        {
            return false;
        }

        if (!r.menuBackgroundTexture.loadFromFile(base + "MenuBackground.png")) 
        {
            return false;
        }

        if (!r.fontUi.loadFromFile(base + k_FontPath)) 
        {
            return false;
        }

        if (!r.fontTitle.loadFromFile(base + "Fonts/ContraPhobotech.otf")) 
        {
            return false;
        }

        return true;
    }
}
