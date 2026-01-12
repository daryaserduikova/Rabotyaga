#pragma once

namespace ApplesGame
{
    constexpr const char* k_ResourcesPath = "Resources/";
    constexpr const char* k_FontPath = "Fonts/Roboto-Regular.ttf";

    constexpr int k_ScreenWidth = 800;
    constexpr int k_ScreenHeight = 600;

    constexpr float k_ScreenWidthF = static_cast<float>(k_ScreenWidth);
    constexpr float k_ScreenHeightF = static_cast<float>(k_ScreenHeight);

    constexpr float k_InitialSpeed = 200.0F;
    constexpr float k_Acceleration = 20.0F;

    constexpr float k_PlayerRadius = 30.0F;
    constexpr float k_AppleRadius = 20.0F;

    constexpr float k_PlayerSize = k_PlayerRadius * 2.0F;
    constexpr float k_AppleSize = k_AppleRadius * 2.0F;

    constexpr float k_MaxDtSeconds = 0.1F;
}
