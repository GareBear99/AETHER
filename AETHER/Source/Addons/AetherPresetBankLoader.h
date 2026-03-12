#pragma once
#include "AetherAddonTypes.h"

namespace aether::addons
{
    struct ExternalPreset
    {
        juce::String name;
        juce::NamedValueSet values;
    };

    struct ExternalPresetBank
    {
        juce::String bankName;
        juce::Array<ExternalPreset> presets;
        AddonLoadReport report;
    };

    class PresetBankLoader
    {
    public:
        static ExternalPresetBank loadFromFolder(const juce::File& addonFolder);
    };
}
