#include "PluginEditor.h"
#include "Presets/AetherPresetBank.h"
#include "Presets/AetherPresetManager.h"
#include "UI/MysticBackground.h"

namespace
{
static float dbToNorm(float dB)
{
    return juce::jlimit(0.0f, 1.0f, (dB + 60.0f) / 60.0f);
}
}

AetherAudioProcessorEditor::AetherAudioProcessorEditor (AetherAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&look);
    setSize(1120, 720);

    title.setText("AETHER", juce::dontSendNotification);
    title.setFont(juce::FontOptions(34.0f, juce::Font::bold));
    title.setJustificationType(juce::Justification::centredLeft);
    title.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(title);

    subtitle.setText("Ethereal Choir Atmosphere Designer", juce::dontSendNotification);
    subtitle.setFont(juce::FontOptions(15.0f));
    subtitle.setJustificationType(juce::Justification::centredLeft);
    subtitle.setColour(juce::Label::textColourId, juce::Colour::fromRGB(225, 214, 255));
    addAndMakeVisible(subtitle);

    styleLabel(meterLabel, 13.0f, juce::Justification::centredRight);
    meterLabel.setColour(juce::Label::textColourId, juce::Colour::fromRGB(255, 231, 171));
    addAndMakeVisible(meterLabel);

    styleLabel(invocationHint, 12.5f, juce::Justification::centredLeft);
    invocationHint.setText("INVOCATION captures a moment and sustains it as a living choir bed.", juce::dontSendNotification);
    invocationHint.setColour(juce::Label::textColourId, juce::Colour::fromRGBA(255, 255, 255, 180));
    addAndMakeVisible(invocationHint);

    styleLabel(loreHint, 12.0f, juce::Justification::centredLeft);
    loreHint.setText("Ghost choir. Sacred bloom. Dark cathedral air.", juce::dontSendNotification);
    loreHint.setColour(juce::Label::textColourId, juce::Colour::fromRGBA(232, 214, 255, 150));
    addAndMakeVisible(loreHint);

    makeKnob(chant, chantL, "CHANT");
    makeKnob(temple, templeL, "TEMPLE");
    makeKnob(halo, haloL, "HALO");
    makeKnob(drone, droneL, "DRONE");
    makeKnob(motion, motionL, "MOTION");
    makeKnob(lightDark, lightDarkL, "LIGHT / DARK");
    makeKnob(mix, mixL, "MIX");
    makeKnob(output, outputL, "OUTPUT");

    freeze.setButtonText("INVOCATION FREEZE");
    freeze.setClickingTogglesState(true);
    freeze.setColour(juce::ToggleButton::tickColourId, juce::Colour::fromRGB(255, 229, 171));
    freeze.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(42, 24, 55));
    addAndMakeVisible(freeze);

    styleLabel(freezeL, 12.5f);
    freezeL.setText("SIGNATURE HOLD", juce::dontSendNotification);
    freezeL.setColour(juce::Label::textColourId, juce::Colour::fromRGB(255, 232, 180));
    addAndMakeVisible(freezeL);

    presetBox.addItemList(AetherPresetManager::getFactoryPresetNames(), 1);
    presetBox.setTextWhenNothingSelected("Factory Invocation");
    presetBox.setSelectedItemIndex(0, juce::dontSendNotification);
    presetBox.onChange = [this]
    {
        const int idx = presetBox.getSelectedItemIndex();
        if (idx >= 0 && idx < (int) kAetherFactoryPresets.size())
            AetherPresetManager::applyPreset(audioProcessor.apvts, kAetherFactoryPresets[(size_t) idx]);
    };
    addAndMakeVisible(presetBox);

    chantA     = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::chant, chant);
    templeA    = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::temple, temple);
    haloA      = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::halo, halo);
    droneA     = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::drone, drone);
    motionA    = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::motion, motion);
    lightDarkA = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::lightDark, lightDark);
    mixA       = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::mix, mix);
    outputA    = std::make_unique<SliderAttachment>(audioProcessor.apvts, aether::IDs::output, output);
    freezeA    = std::make_unique<ButtonAttachment>(audioProcessor.apvts, aether::IDs::freeze, freeze);

   #if AETHER_LITE
    drone.setEnabled(false);
    motion.setEnabled(false);
    lightDark.setEnabled(false);
    freeze.setEnabled(false);
    freezeL.setText("PRO FEATURE", juce::dontSendNotification);
   #endif

    startTimerHz(24);
}

AetherAudioProcessorEditor::~AetherAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void AetherAudioProcessorEditor::styleLabel(juce::Label& l, float size, juce::Justification justification)
{
    l.setFont(juce::FontOptions(size));
    l.setJustificationType(justification);
    l.setColour(juce::Label::textColourId, juce::Colours::white);
}

void AetherAudioProcessorEditor::makeKnob(juce::Slider& s, juce::Label& l, const juce::String& text)
{
    s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 18);
    s.setMouseDragSensitivity(170);
    addAndMakeVisible(s);

    styleLabel(l, 12.5f);
    l.setText(text, juce::dontSendNotification);
    l.setColour(juce::Label::textColourId, juce::Colour::fromRGB(240, 236, 255));
    addAndMakeVisible(l);
}

void AetherAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient bg(juce::Colour::fromRGB(6, 7, 13), 0.0f, 0.0f,
                            juce::Colour::fromRGB(25, 16, 40), 0.0f, (float) getHeight(), false);
    g.setGradientFill(bg);
    g.fillAll();

    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 12));
    for (int i = 0; i < 140; ++i)
    {
        auto x = (float) ((i * 73) % getWidth());
        auto y = (float) ((i * 43) % getHeight());
        g.fillEllipse(x, y, (i % 4 == 0) ? 2.2f : 1.2f, (i % 4 == 0) ? 2.2f : 1.2f);
    }

    auto bounds = getLocalBounds().reduced(18).toFloat();
    aether::ui::drawMysticPanel(g, bounds, 24.0f);

    auto topBar = bounds.removeFromTop(74.0f);
    aether::ui::drawMysticPanel(g, topBar, 18.0f);

    auto bottomStrip = bounds.removeFromBottom(120.0f);
    auto leftPanel = bounds.removeFromLeft(320.0f);
    auto rightPanel = bounds.removeFromRight(320.0f);
    auto center = bounds.reduced(10.0f);

    aether::ui::drawMysticPanel(g, leftPanel, 22.0f);
    aether::ui::drawMysticPanel(g, rightPanel, 22.0f);
    aether::ui::drawMysticPanel(g, center, 28.0f);
    aether::ui::drawMysticPanel(g, bottomStrip, 22.0f);

    auto orb = center.reduced(64.0f, 44.0f);
    orb = juce::Rectangle<float>(orb.getCentreX() - 155.0f, orb.getCentreY() - 155.0f, 310.0f, 310.0f);
    aether::ui::drawOrbAndRunes(g, orb, (float) motion.getValue() / 100.0f, wetNorm);

    g.setColour(juce::Colour::fromRGBA(255, 255, 255, 110));
    g.setFont(juce::FontOptions(14.0f, juce::Font::plain));
    g.drawText("TEMPLE RESONANCE", orb.getX() - 24.0f, orb.getBottom() + 10.0f, orb.getWidth() + 48.0f, 18.0f, juce::Justification::centred);

    auto meterArea = bottomStrip.reduced(14.0f);
    auto m1 = meterArea.removeFromLeft(meterArea.getWidth() / 3.0f).reduced(4.0f);
    auto m2 = meterArea.removeFromLeft(meterArea.getWidth() / 2.0f).reduced(4.0f);
    auto m3 = meterArea.reduced(4.0f);
    aether::ui::drawMeterBar(g, m1, outNorm, "Output Presence");
    aether::ui::drawMeterBar(g, m2, wetNorm, "Wet Bloom");
    aether::ui::drawMeterBar(g, m3, duckNorm, "Aura Density");
}

void AetherAudioProcessorEditor::resized()
{
    auto root = getLocalBounds().reduced(18);
    auto topBar = root.removeFromTop(74).reduced(16, 10);
    title.setBounds(topBar.removeFromLeft(230));
    subtitle.setBounds(topBar.removeFromLeft(330));
    presetBox.setBounds(topBar.removeFromLeft(240).reduced(8, 4));
    meterLabel.setBounds(topBar);

    auto bottomStrip = root.removeFromBottom(120).reduced(14);
    auto leftPanel = root.removeFromLeft(320).reduced(14);
    auto rightPanel = root.removeFromRight(320).reduced(14);
    auto center = root.reduced(14);

    auto leftTop = leftPanel.removeFromTop(leftPanel.getHeight() / 2);
    auto leftBottom = leftPanel;
    auto rightTop = rightPanel.removeFromTop(rightPanel.getHeight() / 2);
    auto rightBottom = rightPanel;

    auto placeTriple = [] (juce::Rectangle<int> area, juce::Slider& a, juce::Label& al, juce::Slider& b, juce::Label& bl, juce::Slider& c, juce::Label& cl)
    {
        area = area.reduced(6);
        const int labelH = 18;
        const int w = area.getWidth() / 3;
        auto placeOne = [labelH] (juce::Rectangle<int> cell, juce::Slider& s, juce::Label& l)
        {
            l.setBounds(cell.removeFromTop(labelH));
            s.setBounds(cell.reduced(2));
        };
        auto c1 = area.removeFromLeft(w);
        auto c2 = area.removeFromLeft(w);
        auto c3 = area;
        placeOne(c1, a, al);
        placeOne(c2, b, bl);
        placeOne(c3, c, cl);
    };

    placeTriple(leftTop, chant, chantL, temple, templeL, halo, haloL);
    placeTriple(rightTop, drone, droneL, motion, motionL, lightDark, lightDarkL);

    auto centerText = center.removeFromBottom(76);
    invocationHint.setBounds(centerText.removeFromTop(20));
    loreHint.setBounds(centerText.removeFromTop(18));

    auto freezeArea = rightBottom.removeFromTop(94).reduced(8);
    freezeL.setBounds(freezeArea.removeFromTop(18));
    freeze.setBounds(freezeArea.removeFromTop(34));

    auto mixArea = leftBottom.removeFromTop(130);
    mixL.setBounds(mixArea.removeFromTop(18));
    mix.setBounds(mixArea.removeFromLeft(138).reduced(2));
    outputL.setBounds(mixArea.removeFromTop(18));
    output.setBounds(mixArea.removeFromLeft(138).reduced(2));

    auto meterArea = bottomStrip;
    auto third = meterArea.getWidth() / 3;
    juce::ignoreUnused(third);
}

void AetherAudioProcessorEditor::timerCallback()
{
    const auto outDb = juce::Decibels::gainToDecibels(audioProcessor.meters.outRms.load() + 1.0e-9f, -100.0f);
    const auto wetDb = juce::Decibels::gainToDecibels(audioProcessor.meters.wetRms.load() + 1.0e-9f, -100.0f);
    const auto duckDb = audioProcessor.meters.duckDb.load();
    outNorm = dbToNorm(outDb);
    wetNorm = dbToNorm(wetDb);
    duckNorm = juce::jlimit(0.0f, 1.0f, (duckDb + 24.0f) / 24.0f);
    meterLabel.setText("OUT " + juce::String(outDb, 1) + " dB    WET " + juce::String(wetDb, 1) + " dB    DENSITY " + juce::String(duckDb, 1) + " dB", juce::dontSendNotification);
    repaint();
}
