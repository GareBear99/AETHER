#pragma once
#include <JuceHeader.h>

class TempleSpace
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void setParameters(float temple, float halo, float lightDark, float motion);
    void process(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& preDelayBuffer, int& writePos);
private:
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters revParams;
    juce::dsp::Chorus<float> chorus;
    double sr = 44100.0;
    float temple = 0.5f;
};
