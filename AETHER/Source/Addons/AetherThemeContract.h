#pragma once
#include <JuceHeader.h>

namespace aether::addons
{
    namespace Contract
    {
        static inline const juce::StringArray parameterIds {
            "param_chant", "param_halo", "param_temple", "param_drone", "param_motion",
            "param_lightdark", "param_mix", "param_output", "param_freeze", "param_formant",
            "param_spread", "param_predelay"
        };

        static inline bool isCanonicalParameter(const juce::String& id)
        {
            return parameterIds.contains(id);
        }
    }
}
