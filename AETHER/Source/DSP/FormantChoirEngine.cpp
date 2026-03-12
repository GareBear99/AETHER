#include "FormantChoirEngine.h"

void FormantChoirEngine::prepare(double sampleRate, int, int)
{
    sr = sampleRate;
    reset();
}

void FormantChoirEngine::reset()
{
    for (int ch = 0; ch < 2; ++ch)
    {
        formantA[ch].reset(); formantB[ch].reset();
        tiltHi[ch].reset(); tiltLo[ch].reset();
    }
}

void FormantChoirEngine::setAmount(float newChant, float newLightDark)
{
    chant = juce::jlimit(0.0f, 1.0f, newChant);
    lightDark = juce::jlimit(-1.0f, 1.0f, newLightDark);

    const float f1 = juce::jmap(chant, 620.0f, 980.0f) * (1.0f + 0.06f * lightDark);
    const float f2 = juce::jmap(chant, 1350.0f, 2300.0f) * (1.0f + 0.08f * lightDark);
    const float q1 = juce::jmap(chant, 0.7f, 2.8f);
    const float q2 = juce::jmap(chant, 0.8f, 3.6f);
    const float lowGain = juce::Decibels::decibelsToGain(juce::jmap(-lightDark, -2.5f, 5.5f));
    const float hiGain  = juce::Decibels::decibelsToGain(juce::jmap( lightDark, -2.0f, 6.0f));

    for (int ch = 0; ch < 2; ++ch)
    {
        formantA[ch].coefficients = Coeff::makePeakFilter(sr, f1, q1, juce::Decibels::decibelsToGain(4.0f + 6.0f * chant));
        formantB[ch].coefficients = Coeff::makePeakFilter(sr, f2, q2, juce::Decibels::decibelsToGain(2.0f + 5.0f * chant));
        tiltLo[ch].coefficients   = Coeff::makeLowShelf(sr, 250.0f, 0.707f, lowGain);
        tiltHi[ch].coefficients   = Coeff::makeHighShelf(sr, 4200.0f, 0.707f, hiGain);
    }
}

void FormantChoirEngine::process(juce::AudioBuffer<float>& buffer)
{
    for (int ch = 0; ch < juce::jmin(2, buffer.getNumChannels()); ++ch)
    {
        juce::dsp::AudioBlock<float> block(buffer.getWritePointer(ch), 1, (size_t) buffer.getNumSamples());
        juce::dsp::ProcessContextReplacing<float> ctx(block);
        formantA[ch].process(ctx);
        formantB[ch].process(ctx);
        tiltLo[ch].process(ctx);
        tiltHi[ch].process(ctx);
    }
}
