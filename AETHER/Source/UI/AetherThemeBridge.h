#pragma once
#include <JuceHeader.h>
#include "../Addons/AetherRuntimeThemeState.h"

namespace aether::ui
{
    struct ThemeVisualState
    {
        juce::Colour backgroundTop    { juce::Colour::fromRGB (6, 7, 13) };
        juce::Colour backgroundBottom { juce::Colour::fromRGB (25, 16, 40) };
        juce::Colour accentGold       { juce::Colour::fromRGB (255, 231, 171) };
        juce::Colour accentText       { juce::Colour::fromRGB (232, 214, 255) };
        juce::String title            { "AETHER" };
        juce::String subtitle         { "Ethereal Choir Atmosphere Designer" };
        juce::String flavorText       { "Ghost choir. Sacred bloom. Dark cathedral air." };
    };

    class ThemeBridge
    {
    public:
        static ThemeVisualState makeVisualState (const aether::addons::RuntimeThemeState& runtime)
        {
            ThemeVisualState state;

            if (runtime.activeAddonId.containsIgnoreCase ("agartha"))
            {
                state.backgroundTop    = juce::Colour::fromRGB (13, 8, 7);
                state.backgroundBottom = juce::Colour::fromRGB (40, 18, 10);
                state.accentGold       = juce::Colour::fromRGB (241, 186, 107);
                state.accentText       = juce::Colour::fromRGB (255, 220, 192);
                state.subtitle         = "Agartha Panel — Subterranean Choir Chamber";
                state.flavorText       = "Buried choir. Molten glyphs. Mineral cathedral heat.";
            }

            return state;
        }
    };
}
