// @file GameRules.h
#pragma once
#include <cstdint>

namespace ApplesGame
{
    enum class EGameRule : uint32_t
    {
        None = 0,

        // Apple count modes
        Finite20 = 1U << 0,
        Finite50 = 1U << 1,
        InfiniteApples = 1U << 2,

        // Speed modifiers
        SpeedUpOnEat = 1U << 3,
        NoSpeedUpOnEat = 1U << 4,
    };

    inline EGameRule operator|(EGameRule a, EGameRule b)
    {
        return static_cast<EGameRule>(
            static_cast<uint32_t>(a) |
            static_cast<uint32_t>(b)
            );
    }

    inline EGameRule operator&(EGameRule a, EGameRule b)
    {
        return static_cast<EGameRule>(
            static_cast<uint32_t>(a) &
            static_cast<uint32_t>(b)
            );
    }

    inline EGameRule operator~(EGameRule a)
    {
        return static_cast<EGameRule>(
            ~static_cast<uint32_t>(a)
            );
    }

    inline EGameRule& operator|=(EGameRule& a, EGameRule b)
    {
        a = a | b;
        return a;
    }

    inline EGameRule& operator&=(EGameRule& a, EGameRule b)
    {
        a = a & b;
        return a;
    }

    // Group masks

    constexpr uint32_t kAppleModesBits =
        (1U << 0) |
        (1U << 1) |
        (1U << 2);

    constexpr uint32_t kSpeedModesBits =
        (1U << 3) |
        (1U << 4);

    constexpr EGameRule kAppleModesMask =
        static_cast<EGameRule>(kAppleModesBits);

    constexpr EGameRule kSpeedModesMask =
        static_cast<EGameRule>(kSpeedModesBits);

    // Helpers

    inline bool HasRule(EGameRule mask, EGameRule rule)
    {
        return (static_cast<uint32_t>(mask) &
            static_cast<uint32_t>(rule)) != 0U;
    }

    inline void SetAppleMode(EGameRule& mask, EGameRule appleMode)
    {
        mask = static_cast<EGameRule>(
            static_cast<uint32_t>(mask) & ~kAppleModesBits
            );

        mask |= appleMode;
    }

    inline void SetSpeedMode(EGameRule& mask, EGameRule speedMode)
    {
        mask = static_cast<EGameRule>(
            static_cast<uint32_t>(mask) & ~kSpeedModesBits
            );

        mask |= speedMode;
    }
}