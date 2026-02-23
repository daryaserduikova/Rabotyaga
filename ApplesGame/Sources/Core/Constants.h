// @file Constants.h
#pragma once

namespace ApplesGame
{
    namespace Paths
    {
        constexpr const char* k_Resources = "Resources/";
        constexpr const char* k_UiFont = "Fonts/Roboto-Regular.ttf";
        constexpr const char* k_TitleFont = "Fonts/ContraPhobotech.otf";
    }

    namespace Screen
    {
        constexpr int k_Width = 800;
        constexpr int k_Height = 600;

        constexpr float k_WidthF = static_cast<float>(k_Width);
        constexpr float k_HeightF = static_cast<float>(k_Height);

        constexpr float k_MaxDtSeconds = 0.1F;
    }

    namespace PlayerConfig
    {
        constexpr float k_InitialSpeed = 200.0F;
        constexpr float k_Acceleration = 20.0F;

        constexpr float k_Radius = 30.0F;
        constexpr float k_Size = k_Radius * 2.0F;
    }

    namespace AppleConfig
    {
        constexpr float k_Radius = 20.0F;
        constexpr float k_Size = k_Radius * 2.0F;
    }

    namespace UIConfig
    {
        // Splash
        constexpr float k_SplashFadeSeconds = 1.0F;
        constexpr float k_SplashBlinkHz = 0.6F; // blink
        constexpr float k_TwoPi = 6.28318530718F;

        // Choose placement
        constexpr float k_ChooseListCenterX = Screen::k_WidthF / 2.0F + 10.0F;
        constexpr float k_ChooseListCenterY = Screen::k_HeightF / 2.0F + 10.0F;

        // Offsets
        constexpr float k_ChooseListOffsetY = -20.0F;
        constexpr float k_ChooseStartOffsetY = 120.0F;
    }
}