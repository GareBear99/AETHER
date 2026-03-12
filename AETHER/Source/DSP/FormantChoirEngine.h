#pragma once
#include <JuceHeader.h>

class FormantChoirEngine
{
public:
    void prepare(double sampleRate, int maxBlock, int channels);
    void reset();
    void setAmount(float chant, float lightDark);
    void process(juce::AudioBuffer<float>& buffer);

private:
    using Filter = juce::dsp::IIR::Filter<float>;
    using Coeff  = juce::dsp::IIR::Coefficients<float>;

    double sr = 44100.0;
    float chant = 0.4f, lightDark = 0.0f;
    Filter formantA[2], formantB[2], tiltHi[2], tiltLo[2];
};
