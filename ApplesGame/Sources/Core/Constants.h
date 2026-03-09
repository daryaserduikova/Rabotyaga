// @file Constants.h
#pragma once

#include <SFML/Graphics.hpp>

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
        // Font sizes
        constexpr unsigned int k_HudSize = 24;
        constexpr unsigned int k_TitleSize = 54;
        constexpr unsigned int k_MenuTitleSize = 48;
        constexpr unsigned int k_ChooseTitleSize = 36;
        constexpr unsigned int k_ChooseListSize = 20;
        constexpr unsigned int k_StartSize = 34;
        constexpr unsigned int k_GameOverSize = 36;
        constexpr unsigned int k_LeaderboardSize = 22;
        constexpr unsigned int k_ApplesEatenSize = 24;

        // Main menu layout
        constexpr float k_MainTitleY = 160.0F;
        constexpr float k_MainPlayY = 280.0F;
        constexpr float k_MainExitY = 320.0F;

        // Choose menu layout
        constexpr float k_ChooseTitleY = 90.0F;
        constexpr float k_ChooseListLeftX = 305.0F;
        constexpr float k_ChooseListTopY = 175.0F;
        constexpr float k_ChooseLineStep = 28.0F;
        constexpr float k_ChooseSpeedHeaderLine = 4.6F;
        constexpr float k_ChooseSpeedUpLine = 5.6F;
        constexpr float k_ChooseNoSpeedUpLine = 6.6F;
        constexpr float k_ChooseStartLine = 8.0F;

        // Game over layout
        constexpr float k_GameOverTitleY = 220.0F;
        constexpr float k_GameOverMenuY = 345.0F;

        // Leaderboard layout
        constexpr float k_LeaderboardTitleY = 105.0F;
        constexpr float k_LeaderboardLeftX = 225.0F;
        constexpr float k_LeaderboardRightX = 585.0F;
        constexpr float k_LeaderboardFirstRowY = 180.0F;
        constexpr float k_LeaderboardRowStep = 34.0F;
        constexpr float k_LeaderboardBackY = 540.0F;

        // HUD layout
        constexpr float k_HudScoreX = Screen::k_WidthF - 140.0F;
        constexpr float k_HudScoreY = 20.0F;

        // Colors
        const sf::Color k_ColorWhite(255, 255, 255);
        const sf::Color k_ColorHud(255, 255, 255, 160);
        const sf::Color k_ColorChooseHeader(95, 55, 25);
        const sf::Color k_ColorChooseList(125, 85, 45);
        const sf::Color k_ColorChooseListActive(170, 115, 55);
        const sf::Color k_ColorStart(190, 140, 60);
        const sf::Color k_ColorStartActive(240, 190, 90);
        const sf::Color k_ColorGameOver(255, 0, 0);

        // Outline
        constexpr float k_TextOutlineThickness = 2.0F;
        const sf::Color k_TextOutlineColor(45, 20, 10);

        constexpr float k_TitleOutlineThickness = 3.0F;
        const sf::Color k_TitleOutlineColor(60, 25, 10);

        constexpr float k_GameOverOutlineThickness = 2.0F;
        const sf::Color k_GameOverOutlineColor(70, 0, 0);
    }
}