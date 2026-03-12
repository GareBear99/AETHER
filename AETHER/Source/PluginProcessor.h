#pragma once
#include <JuceHeader.h>
#include "Core/AetherParameters.h"
#include "Core/AetherMeterState.h"
#include "DSP/AetherDSPChain.h"

class AetherAudioProcessor final : public juce::AudioProcessor,
                                   private juce::AudioProcessorValueTreeState::Listener
{
public:
    AetherAudioProcessor();
    ~AetherAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override;
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 5.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    AetherMeterState meters;

private:
    void parameterChanged (const juce::String&, float) override;
    void refreshMacros();

    std::atomic<bool> dirty { true };
    AetherDSPChain dsp;

    float chant = 0.45f, temple = 0.55f, halo = 0.4f, drone = 0.2f, motion = 0.25f, lightDark = 0.0f, mix = 0.35f, outputDb = 0.0f;
    bool freeze = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AetherAudioProcessor)
};
