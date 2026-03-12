#include "AetherDSPChain.h"

float AetherDSPChain::rmsOf(const juce::AudioBuffer<float>& b)
{
    double acc = 0.0; int count = 0;
    for (int ch = 0; ch < b.getNumChannels(); ++ch)
    {
        const auto* d = b.getReadPointer(ch);
        for (int i = 0; i < b.getNumSamples(); ++i) { acc += d[i] * d[i]; ++count; }
    }
    return count > 0 ? std::sqrt((float) (acc / (double) count)) : 0.0f;
}

void AetherDSPChain::prepare(double sampleRate, int samplesPerBlock, int channels)
{
    sr = sampleRate;
    dryCopy.setSize(channels, samplesPerBlock, false, false, true);
    wetBuffer.setSize(channels, samplesPerBlock, false, false, true);
    tempBuffer.setSize(channels, samplesPerBlock, false, false, true);

    const int maxDelaySamps = (int) std::ceil(0.15 * sr) + samplesPerBlock + 4;
    preDelayBuffer.setSize(channels, maxDelaySamps, false, false, true);
    preDelayBuffer.clear();
    preDelayWrite = 0;

    juce::dsp::ProcessSpec spec { sampleRate, (juce::uint32) samplesPerBlock, (juce::uint32) channels };
    templeSpace.prepare(spec);
    choir.prepare(sampleRate, samplesPerBlock, channels);
    invocation.prepare(sampleRate, samplesPerBlock, channels);
    reset();
}

void AetherDSPChain::reset()
{
    templeSpace.reset();
    choir.reset();
    invocation.reset();
    preDelayBuffer.clear();
    preDelayWrite = 0;
}

void AetherDSPChain::setMacroState(float c, float t, float h, float d, float m, float ld, float mx, float outDb, bool frz)
{
    chant = c; temple = t; halo = h; drone = d; motion = m; lightDark = ld; mix = mx; outputDb = outDb; freeze = frz;
    choir.setAmount(chant, lightDark);
    haloEngine.setAmount(halo);
    invocation.setAmount(drone, freeze);
    templeSpace.setParameters(temple, halo, lightDark, motion);
}

void AetherDSPChain::process(juce::AudioBuffer<float>& buffer, AetherMeterState& meters)
{
    dryCopy.makeCopyOf(buffer, true);
    wetBuffer.makeCopyOf(buffer, true);

    templeSpace.process(wetBuffer, preDelayBuffer, preDelayWrite);
    invocation.process(wetBuffer);
    choir.process(wetBuffer);
    haloEngine.process(wetBuffer, tempBuffer);

    const float outLin = juce::Decibels::decibelsToGain(outputDb);
    const float dryMix = 1.0f - mix;

    for (int ch = 0; ch < juce::jmin(2, buffer.getNumChannels()); ++ch)
    {
        auto* dst = buffer.getWritePointer(ch);
        const auto* dry = dryCopy.getReadPointer(ch);
        const auto* wet = wetBuffer.getReadPointer(ch);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
            dst[i] = outLin * (dryMix * dry[i] + mix * wet[i]);
    }

    const float wetRms = rmsOf(wetBuffer);
    const float dryRms = rmsOf(dryCopy);
    const float outRms = rmsOf(buffer);
    meters.wetRms.store(wetRms);
    meters.dryRms.store(dryRms);
    meters.outRms.store(outRms);
    meters.duckDb.store(juce::Decibels::gainToDecibels((dryRms > 1.0e-6f && wetRms > 1.0e-6f) ? wetRms / dryRms : 1.0f));
}
