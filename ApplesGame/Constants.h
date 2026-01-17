#pragma once

namespace ApplesGame
{
    namespace Paths
    {
        constexpr const char* Resources = "Resources/";
        constexpr const char* UiFont = "Fonts/Roboto-Regular.ttf";
    }

    namespace Screen
    {
        constexpr int Width = 800;
        constexpr int Height = 600;

        constexpr float WidthF = static_cast<float>(Width);
        constexpr float HeightF = static_cast<float>(Height);

        constexpr float MaxDtSeconds = 0.1F;
    }

    namespace PlayerConfig
    {
        constexpr float InitialSpeed = 200.0F;
        constexpr float Acceleration = 20.0F;

        constexpr float Radius = 30.0F;
        constexpr float Size = Radius * 2.0F;
    }

    namespace AppleConfig
    {
        constexpr float Radius = 20.0F;
        constexpr float Size = Radius * 2.0F;
    }
}
