#pragma once
#include <JuceHeader.h>
#include "AetherAddonHost.h"

namespace aether::addons
{
    struct RuntimeThemeState
    {
        juce::String activeAddonId { "com.aether.theme.default" };
        juce::String activeThemeName { "Default" };
        juce::StringArray warnings;
        juce::StringArray availableThemeIds;
        bool addonModeAvailable = false;

        void refreshFromHost (const AddonHost& host)
        {
            warnings = host.getBootWarnings();
            availableThemeIds.clearQuick();

            for (const auto& addon : host.getRegistry().getAddons())
                availableThemeIds.add (addon.manifest.id);

            if (const auto* theme = host.getActiveTheme())
            {
                activeAddonId = theme->manifest.id;
                activeThemeName = theme->manifest.name;
                addonModeAvailable = true;
            }
            else
            {
                activeAddonId = "com.aether.theme.default";
                activeThemeName = "Default";
                addonModeAvailable = false;
            }
        }
    };
}
