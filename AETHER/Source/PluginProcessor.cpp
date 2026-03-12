#include "PluginProcessor.h"
#include "PluginEditor.h"

AetherAudioProcessor::AetherAudioProcessor()
: AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                   .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
  apvts(*this, nullptr, "PARAMS", aether::createParameterLayout())
{
    for (auto* id : { aether::IDs::chant, aether::IDs::temple, aether::IDs::halo,
                      aether::IDs::drone, aether::IDs::motion, aether::IDs::lightDark,
                      aether::IDs::mix, aether::IDs::output, aether::IDs::freeze })
        apvts.addParameterListener(id, this);
}

AetherAudioProcessor::~AetherAudioProcessor()
{
    for (auto* id : { aether::IDs::chant, aether::IDs::temple, aether::IDs::halo,
                      aether::IDs::drone, aether::IDs::motion, aether::IDs::lightDark,
                      aether::IDs::mix, aether::IDs::output, aether::IDs::freeze })
        apvts.removeParameterListener(id, this);
}

const juce::String AetherAudioProcessor::getName() const
{
   #if AETHER_LITE
    return "Aether Lite";
   #else
    return "Aether";
   #endif
}

void AetherAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp.prepare(sampleRate, juce::jmax(64, samplesPerBlock), 2);
    dirty.store(true);
    refreshMacros();
}

void AetherAudioProcessor::releaseResources() {}

bool AetherAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void AetherAudioProcessor::parameterChanged (const juce::String&, float)
{
    dirty.store(true, std::memory_order_release);
}

void AetherAudioProcessor::refreshMacros()
{
    auto getNorm = [this](const char* id)
    {
        return apvts.getRawParameterValue(id)->load();
    };

    chant = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::chant) / 100.0f);
    temple = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::temple) / 100.0f);
    halo = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::halo) / 100.0f);
   #if AETHER_PRO
    drone = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::drone) / 100.0f);
    motion = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::motion) / 100.0f);
    lightDark = juce::jlimit(-1.0f, 1.0f, getNorm(aether::IDs::lightDark) / 100.0f);
    freeze = apvts.getRawParameterValue(aether::IDs::freeze)->load() > 0.5f;
   #else
    drone = 0.0f; motion = 0.0f; lightDark = 0.0f; freeze = false;
   #endif
    mix = juce::jlimit(0.0f, 1.0f, getNorm(aether::IDs::mix) / 100.0f);
    outputDb = getNorm(aether::IDs::output);

    dsp.setMacroState(chant, temple, halo, drone, motion, lightDark, mix, outputDb, freeze);
}

void AetherAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    if (dirty.exchange(false, std::memory_order_acq_rel))
        refreshMacros();
    dsp.process(buffer, meters);
}

juce::AudioProcessorEditor* AetherAudioProcessor::createEditor()
{
    return new AetherAudioProcessorEditor(*this);
}

void AetherAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary(*xml, destData);
}

void AetherAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        if (xml->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xml));
    dirty.store(true);
}
