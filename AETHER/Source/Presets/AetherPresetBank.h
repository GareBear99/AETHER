#pragma once
#include <array>
#include <JuceHeader.h>

struct AetherPreset
{
    const char* name;
    float chant, temple, halo, drone, motion, lightDark, mix, output;
    bool freeze;
};

static constexpr std::array<AetherPreset, 10> kAetherFactoryPresets {{
    { "Celestial Procession", 56, 68, 55, 24, 28, 35, 38, 0, false },
    { "Black Halo",           48, 72, 61, 34, 20, -42, 40, 0, false },
    { "Hollow Chapel",        63, 78, 32, 22, 18, -18, 45, 0, false },
    { "Lantern Choir",        58, 54, 46, 18, 30, 22, 33, 0, false },
    { "Grave Hymn",           71, 80, 25, 42, 16, -55, 48, -1, false },
    { "Sainted Air",          38, 62, 70, 12, 34, 52, 36, 0, false },
    { "Glass Cathedral",      52, 75, 76, 14, 40, 48, 42, 0, false },
    { "Astral Choir",         60, 64, 59, 28, 36, 30, 39, 0, false },
    { "Morning Incense",      34, 50, 44, 16, 21, 18, 31, 0, false },
    { "Ancient Ritual",       67, 82, 37, 40, 19, -22, 46, -1, true  },
}};
