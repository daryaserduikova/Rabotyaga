#include "Logger.h"
#include <iostream>

namespace ApplesGame
{
    void LogError(const std::string& msg)
    {
        std::cerr << "[ERROR] " << msg << "\n";
    }
}
