#pragma once
#include "AetherAddonTypes.h"

namespace aether::addons
{
    class ThemeValidator
    {
    public:
        static AddonLoadReport validateManifest(const AddonManifest& manifest);
        static AddonLoadReport validatePanel(const PanelTheme& panel, const juce::File& rootFolder);
        static AddonLoadReport validateLayout(const LayoutDefinition& layout);
        static AddonLoadReport validateAll(const LoadedAddon& addon);
        static bool isKnownParameter(const juce::String& paramId);
    };
}
