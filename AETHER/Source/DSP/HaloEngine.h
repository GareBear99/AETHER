#pragma once
#include <JuceHeader.h>

class HaloEngine
{
public:
    void setAmount(float haloAmount) { halo = juce::jlimit(0.0f, 1.0f, haloAmount); }
    void process(juce::AudioBuffer<float>& wetBuffer, juce::AudioBuffer<float>& tempBuffer);
private:
    float halo = 0.35f;
};
