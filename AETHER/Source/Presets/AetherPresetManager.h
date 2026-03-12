#pragma once
#include <JuceHeader.h>
#include "AetherPresetBank.h"

class AetherPresetManager
{
public:
    static void applyPreset(juce::AudioProcessorValueTreeState& apvts, const AetherPreset& preset);
    static juce::StringArray getFactoryPresetNames();
};
