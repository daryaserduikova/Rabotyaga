// @file Utils.h

#pragma once

namespace ApplesGame
{
    inline float Clamp01(float value)
    {
        if (value < 0.0F)
        {
            return 0.0F;
        }

        if (value > 1.0F)
        {
            return 1.0F;
        }

        return value;
    }
}
