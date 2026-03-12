#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AetherLookAndFeel.h"

class AetherAudioProcessorEditor final : public juce::AudioProcessorEditor,
                                         private juce::Timer
{
public:
    explicit AetherAudioProcessorEditor (AetherAudioProcessor&);
    ~AetherAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    void timerCallback() override;
    void makeKnob(juce::Slider& slider, juce::Label& label, const juce::String& text);
    void styleLabel(juce::Label& l, float size = 13.0f, juce::Justification justification = juce::Justification::centred);

    AetherAudioProcessor& audioProcessor;
    AetherLookAndFeel look;

    juce::Slider chant, temple, halo, drone, motion, lightDark, mix, output;
    juce::ToggleButton freeze;
    juce::Label chantL, templeL, haloL, droneL, motionL, lightDarkL, mixL, outputL, freezeL;
    juce::ComboBox presetBox;
    juce::Label title, subtitle, meterLabel, invocationHint, loreHint;

    float wetNorm = 0.0f, outNorm = 0.0f, duckNorm = 0.0f;

    std::unique_ptr<SliderAttachment> chantA, templeA, haloA, droneA, motionA, lightDarkA, mixA, outputA;
    std::unique_ptr<ButtonAttachment> freezeA;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AetherAudioProcessorEditor)
};
