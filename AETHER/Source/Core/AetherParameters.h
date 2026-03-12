#pragma once
#include <JuceHeader.h>

namespace aether
{
namespace IDs
{
    static constexpr auto chant     = "chant";
    static constexpr auto temple    = "temple";
    static constexpr auto halo      = "halo";
    static constexpr auto drone     = "drone";
    static constexpr auto motion    = "motion";
    static constexpr auto lightDark = "lightdark";
    static constexpr auto mix       = "mix";
    static constexpr auto output    = "output";
    static constexpr auto freeze    = "freeze";
}

inline juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    using P = std::unique_ptr<juce::RangedAudioParameter>;
    std::vector<P> params;

    auto percent = [] (const juce::String& id, const juce::String& name, float def)
    {
        return std::make_unique<juce::AudioParameterFloat>(id, name,
            juce::NormalisableRange<float>(0.0f, 100.0f, 0.01f), def);
    };

    params.push_back(percent(IDs::chant, "Chant", 45.0f));
    params.push_back(percent(IDs::temple, "Temple", 55.0f));
    params.push_back(percent(IDs::halo, "Halo", 40.0f));
    params.push_back(percent(IDs::drone, "Drone", 20.0f));
    params.push_back(percent(IDs::motion, "Motion", 25.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(IDs::lightDark, "LightDark",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 0.01f), 5.0f));
    params.push_back(percent(IDs::mix, "Mix", 35.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(IDs::output, "Output",
        juce::NormalisableRange<float>(-24.0f, 12.0f, 0.01f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>(IDs::freeze, "Freeze", false));

    return { params.begin(), params.end() };
}
} // namespace aether
