#include "AetherPresetManager.h"
#include "../Core/AetherParameters.h"

void AetherPresetManager::applyPreset(juce::AudioProcessorValueTreeState& apvts, const AetherPreset& p)
{
    auto set = [&apvts](const char* id, float v)
    {
        if (auto* param = apvts.getParameter(id))
            param->setValueNotifyingHost(param->convertTo0to1(v));
    };

    set(aether::IDs::chant, p.chant);
    set(aether::IDs::temple, p.temple);
    set(aether::IDs::halo, p.halo);
    set(aether::IDs::drone, p.drone);
    set(aether::IDs::motion, p.motion);
    set(aether::IDs::lightDark, p.lightDark);
    set(aether::IDs::mix, p.mix);
    set(aether::IDs::output, p.output);
    if (auto* param = apvts.getParameter(aether::IDs::freeze))
        param->setValueNotifyingHost(p.freeze ? 1.0f : 0.0f);
}

juce::StringArray AetherPresetManager::getFactoryPresetNames()
{
    juce::StringArray names;
    for (const auto& p : kAetherFactoryPresets)
        names.add(p.name);
    return names;
}
