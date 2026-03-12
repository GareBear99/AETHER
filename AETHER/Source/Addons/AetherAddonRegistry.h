#pragma once
#include "AetherAddonTypes.h"

namespace aether::addons
{
    class AddonRegistry
    {
    public:
        void scanDirectory(const juce::File& themesFolder);
        const juce::Array<LoadedAddon>& getAddons() const noexcept { return addons; }
    private:
        juce::Array<LoadedAddon> addons;
    };
}
