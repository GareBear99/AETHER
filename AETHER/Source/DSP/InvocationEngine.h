#pragma once
#include <JuceHeader.h>

class InvocationEngine
{
public:
    void prepare(double sampleRate, int maxBlock, int channels);
    void reset();
    void setAmount(float droneAmount, bool freezeEnabled);
    void process(juce::AudioBuffer<float>& wetBuffer);
private:
    juce::AudioBuffer<float> freezeBuffer;
    int writePos = 0;
    float drone = 0.2f;
    bool freeze = false;
};
