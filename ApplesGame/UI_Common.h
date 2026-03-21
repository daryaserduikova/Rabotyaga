#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <initializer_list>

#include "Constants.h"

namespace ApplesGame
{
    inline void CenterText(sf::Text& text, float x, float y)
    {
        auto b = text.getLocalBounds();
        text.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
        text.setPosition(x, y);
    }

    inline void LeftAlignText(sf::Text& text, float x, float y)
    {
        auto b = text.getLocalBounds();
        text.setOrigin(b.left, b.top);
        text.setPosition(x, y);
    }

    inline void RightAlignText(sf::Text& text, float x, float y)
    {
        auto b = text.getLocalBounds();
        text.setOrigin(b.left + b.width, b.top);
        text.setPosition(x, y);
    }

    inline std::string MakeMenuLine(bool sel, const std::string& t)
    {
        return std::string(sel ? "> " : "  ") + t;
    }

    inline std::string MakeChooseLine(bool sel, bool checked, const std::string& t)
    {
        return std::string(sel ? "> " : "  ") + (checked ? "[x] " : "[ ] ") + t;
    }

    inline std::string MakeLeaderboardEntryLine(int place, const std::string& name)
    {
        std::string s = std::to_string(place) + ". " + name + " ";
        while (s.size() < 50) s += '.';
        return s;
    }

    inline void SetupMenuText(sf::Text& t, const sf::Font& f, unsigned int size, const sf::Color& c)
    {
        t.setFont(f);
        t.setCharacterSize(size);
        t.setFillColor(c);
        t.setOutlineThickness(0.f);
        t.setOutlineColor(UIConfig::k_TextOutlineColor);
    }
}