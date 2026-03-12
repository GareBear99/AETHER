#include "HaloEngine.h"

void HaloEngine::process(juce::AudioBuffer<float>& wetBuffer, juce::AudioBuffer<float>& tempBuffer)
{
    tempBuffer.setSize(wetBuffer.getNumChannels(), wetBuffer.getNumSamples(), false, false, true);
    tempBuffer.clear();

    for (int ch = 0; ch < juce::jmin(2, wetBuffer.getNumChannels()); ++ch)
    {
        auto* wet = wetBuffer.getWritePointer(ch);
        auto* tmp = tempBuffer.getWritePointer(ch);
        for (int i = 0; i < wetBuffer.getNumSamples(); ++i)
        {
            const float x = wet[i];
            const float overtone = std::tanh(std::abs(x) * (1.0f + 2.5f * halo)) * (x >= 0.0f ? 1.0f : -1.0f);
            tmp[i] = 0.28f * halo * overtone;
        }
    }

    for (int ch = 0; ch < juce::jmin(2, wetBuffer.getNumChannels()); ++ch)
        wetBuffer.addFrom(ch, 0, tempBuffer, ch, 0, wetBuffer.getNumSamples(), 1.0f);
}
