#pragma once
#include <cstdint>

namespace ApplesGame
{
    enum class EGameRule : uint32_t
    {
        None = 0,

        Finite20 = 1U << 0,
        Finite50 = 1U << 1,
        InfiniteApples = 1U << 2,

        SpeedUpOnEat = 1U << 3,
        NoSpeedUpOnEat = 1U << 4,
    };

    inline EGameRule operator|(EGameRule a, EGameRule b)
    {
        return static_cast<EGameRule>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline EGameRule operator&(EGameRule a, EGameRule b)
    {
        return static_cast<EGameRule>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    inline EGameRule& operator|=(EGameRule& a, EGameRule b)
    {
        a = a | b;
        return a;
    }

    inline bool HasRule(EGameRule mask, EGameRule rule)
    {
        return static_cast<uint32_t>(mask & rule) != 0U;
    }

    inline void SetAppleMode(EGameRule& mask, EGameRule appleMode)
    {
        mask = static_cast<EGameRule>(
            (static_cast<uint32_t>(mask) &
                ~(static_cast<uint32_t>(EGameRule::Finite20) |
                    static_cast<uint32_t>(EGameRule::Finite50) |
                    static_cast<uint32_t>(EGameRule::InfiniteApples)))
            );
        mask |= appleMode;
    }

    inline void SetSpeedMode(EGameRule& mask, EGameRule speedMode)
    {
        mask = static_cast<EGameRule>(
            (static_cast<uint32_t>(mask) &
                ~(static_cast<uint32_t>(EGameRule::SpeedUpOnEat) |
                    static_cast<uint32_t>(EGameRule::NoSpeedUpOnEat)))
            );
        mask |= speedMode;
    }
}
