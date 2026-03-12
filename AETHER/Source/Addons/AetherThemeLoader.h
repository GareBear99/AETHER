#pragma once
#include "AetherAddonTypes.h"

namespace aether::addons
{
    class ThemeLoader
    {
    public:
        static LoadedAddon loadFromFolder(const juce::File& addonFolder);
    private:
        static AddonManifest parseManifest(const juce::var& value);
        static PanelTheme parsePanel(const juce::var& value);
        static LayoutDefinition parseLayout(const juce::var& value);
        static juce::var readJson(const juce::File& file, juce::String& error);
    };
}
