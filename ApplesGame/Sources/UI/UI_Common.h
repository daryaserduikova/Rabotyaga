//@file UI_Common.h

#pragma once

#include <SFML/Graphics.hpp>
#include <initializer_list>
#include <string>

#include "Constants.h"

namespace ApplesGame
{
    inline void CenterText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(
            bounds.left + bounds.width * 0.5f,
            bounds.top + bounds.height * 0.5f);
        text.setPosition(x, y);
    }

    inline void LeftAlignText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left, bounds.top);
        text.setPosition(x, y);
    }

    inline void RightAlignText(sf::Text& text, float x, float y)
    {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width, bounds.top);
        text.setPosition(x, y);
    }

    inline const char* Check(bool value)
    {
        return value ? "[x] " : "[ ] ";
    }

    inline std::string MakeMenuLine(bool selected, const std::string& text)
    {
        return std::string(selected ? "> " : "  ") + text;
    }

    inline std::string MakeChooseLine(bool selected, bool checked, const std::string& label)
    {
        return std::string(selected ? "> " : "  ") + Check(checked) + label;
    }

    inline std::string MakeLeaderboardEntryLine(int place, const std::string& name)
    {
        std::string line = std::to_string(place) + ". " + name + " ";
        while (line.size() < 50)
        {
            line += '.';
        }
        return line;
    }

    inline void SetupMenuText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& color)
    {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setOutlineThickness(0.0f);
        text.setOutlineColor(UIConfig::k_TextOutlineColor);
    }

    inline void SetSelectedStyle(
        sf::Text& text,
        bool selected,
        const sf::Color& baseColor,
        const sf::Color& selectedColor)
    {
        text.setFillColor(selected ? selectedColor : baseColor);

        if (selected)
        {
            text.setOutlineThickness(UIConfig::k_TextOutlineThickness);
            text.setOutlineColor(UIConfig::k_TextOutlineColor);
        }
        else
        {
            text.setOutlineThickness(0.0f);
        }
    }

    struct TextSelectionStyle
    {
        sf::Text* text = nullptr;
        bool selected = false;
        sf::Color baseColor = sf::Color::White;
        sf::Color selectedColor = sf::Color::White;
    };

    inline void ApplySelectionStyles(const std::initializer_list<TextSelectionStyle>& styles)
    {
        for (const TextSelectionStyle& style : styles)
        {
            if (style.text != nullptr)
            {
                SetSelectedStyle(
                    *style.text,
                    style.selected,
                    style.baseColor,
                    style.selectedColor);
            }
        }
    }
}