#pragma once
#include "AetherAddonRegistry.h"
#include "AetherPresetBankLoader.h"

namespace aether::addons
{
    class AddonHost
    {
    public:
        bool initialise(const juce::File& themesFolder);
        bool activateTheme(const juce::String& addonId);

        const LoadedAddon* getActiveTheme() const noexcept { return activeTheme; }
        const AddonRegistry& getRegistry() const noexcept { return registry; }
        const ExternalPresetBank& getActivePresetBank() const noexcept { return activePresetBank; }
        const juce::StringArray& getBootWarnings() const noexcept { return bootWarnings; }

    private:
        AddonRegistry registry;
        const LoadedAddon* activeTheme = nullptr;
        ExternalPresetBank activePresetBank;
        juce::StringArray bootWarnings;
    };
}
