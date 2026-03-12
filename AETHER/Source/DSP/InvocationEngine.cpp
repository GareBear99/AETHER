#include "InvocationEngine.h"

void InvocationEngine::prepare(double sampleRate, int, int channels)
{
    const int freezeLen = (int) std::ceil(2.0 * sampleRate);
    freezeBuffer.setSize(channels, freezeLen, false, false, true);
    reset();
}

void InvocationEngine::reset()
{
    freezeBuffer.clear();
    writePos = 0;
}

void InvocationEngine::setAmount(float droneAmount, bool freezeEnabled)
{
    drone = juce::jlimit(0.0f, 1.0f, droneAmount);
    freeze = freezeEnabled;
}

void InvocationEngine::process(juce::AudioBuffer<float>& wetBuffer)
{
    const int channels = juce::jmin(2, wetBuffer.getNumChannels());
    const int samples = wetBuffer.getNumSamples();

    for (int ch = 0; ch < channels; ++ch)
    {
        auto* wet = wetBuffer.getWritePointer(ch);
        auto* frz = freezeBuffer.getWritePointer(ch);
        for (int i = 0; i < samples; ++i)
        {
            const int idx = (writePos + i) % freezeBuffer.getNumSamples();
            if (freeze)
            {
                frz[idx] = 0.997f * frz[idx] + 0.003f * wet[i];
                wet[i]   = 0.72f * wet[i] + 0.55f * frz[idx];
            }
            else
            {
                frz[idx] = 0.9993f * frz[idx] + 0.0007f * wet[i];
                wet[i]  += 0.22f * drone * frz[idx];
            }
        }
    }

    writePos = (writePos + samples) % freezeBuffer.getNumSamples();
}
