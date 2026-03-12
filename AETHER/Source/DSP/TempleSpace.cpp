#include "TempleSpace.h"

void TempleSpace::prepare(const juce::dsp::ProcessSpec& spec)
{
    sr = spec.sampleRate;
    reset();
    chorus.prepare(spec);
    chorus.setCentreDelay(9.0f);
    chorus.setDepth(0.18f);
    chorus.setFeedback(0.07f);
    chorus.setMix(0.35f);
}

void TempleSpace::reset()
{
    reverb.reset();
    chorus.reset();
}

void TempleSpace::setParameters(float newTemple, float halo, float lightDark, float motion)
{
    temple = juce::jlimit(0.0f, 1.0f, newTemple);
    revParams.roomSize = juce::jmap(temple, 0.18f, 0.97f);
    revParams.damping  = juce::jlimit(0.1f, 0.92f, 0.60f - 0.22f * lightDark + 0.12f * (1.0f - halo));
    revParams.wetLevel = juce::jmap(temple, 0.16f, 0.52f);
    revParams.dryLevel = 0.0f;
    revParams.width    = juce::jmap(halo, 0.65f, 1.0f);
    revParams.freezeMode = 0.0f;
    reverb.setParameters(revParams);

    chorus.setRate(0.03f + 0.45f * motion);
    chorus.setDepth(0.04f + 0.25f * motion);
    chorus.setCentreDelay(7.0f + 7.0f * halo);
    chorus.setFeedback(0.02f + 0.11f * motion);
    chorus.setMix(0.16f + 0.38f * halo);
}

void TempleSpace::process(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& preDelayBuffer, int& writePos)
{
    const int samples = buffer.getNumSamples();
    const int delaySamps = (int) juce::jmap(temple, 0.0f, 0.12f * (float) sr);
    const int delayLen = preDelayBuffer.getNumSamples();

    for (int ch = 0; ch < juce::jmin(2, buffer.getNumChannels()); ++ch)
    {
        auto* src = buffer.getWritePointer(ch);
        auto* pd = preDelayBuffer.getWritePointer(ch);
        for (int i = 0; i < samples; ++i)
        {
            const int readIdx = (writePos + i - delaySamps + delayLen) % delayLen;
            const float in = src[i];
            src[i] = pd[readIdx];
            pd[(writePos + i) % delayLen] = in;
        }
    }
    writePos = (writePos + samples) % preDelayBuffer.getNumSamples();

    juce::dsp::AudioBlock<float> wetBlock(buffer);
    chorus.process(juce::dsp::ProcessContextReplacing<float>(wetBlock));
    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), samples);
}
