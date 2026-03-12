#pragma once
#include <JuceHeader.h>
#include "FormantChoirEngine.h"
#include "HaloEngine.h"
#include "InvocationEngine.h"
#include "TempleSpace.h"
#include "../Core/AetherMeterState.h"

class AetherDSPChain
{
public:
    void prepare(double sampleRate, int samplesPerBlock, int channels);
    void reset();
    void setMacroState(float chant, float temple, float halo, float drone, float motion, float lightDark, float mix, float outputDb, bool freeze);
    void process(juce::AudioBuffer<float>& buffer, AetherMeterState& meters);

private:
    static float rmsOf(const juce::AudioBuffer<float>& b);

    double sr = 44100.0;
    float chant = 0.45f, temple = 0.55f, halo = 0.4f, drone = 0.2f, motion = 0.25f, lightDark = 0.0f, mix = 0.35f, outputDb = 0.0f;
    bool freeze = false;

    juce::AudioBuffer<float> dryCopy, wetBuffer, tempBuffer, preDelayBuffer;
    int preDelayWrite = 0;

    FormantChoirEngine choir;
    HaloEngine haloEngine;
    InvocationEngine invocation;
    TempleSpace templeSpace;
};
