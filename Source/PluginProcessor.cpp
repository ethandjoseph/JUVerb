#include "PluginProcessor.h"
#include "PluginEditor.h"

JUverbAudioProcessor::JUverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

JUverbAudioProcessor::~JUverbAudioProcessor()
{
}

const juce::String JUverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JUverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JUverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JUverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JUverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JUverbAudioProcessor::getNumPrograms()
{
    return 1;
}

int JUverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JUverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JUverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void JUverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void JUverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    juVerb.prepare(spec);
}

void JUverbAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JUverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Process Block ==============================================================================
void JUverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
	float roomSize = *apvts.getRawParameterValue("ROOM_SIZE");
	float damping = *apvts.getRawParameterValue("DAMPING");
	float width = *apvts.getRawParameterValue("WIDTH");
	bool freeze = *apvts.getRawParameterValue("FREEZE");
	float dry = *apvts.getRawParameterValue("DRY")/100;
	float wet = *apvts.getRawParameterValue("WET")/100;
	juVerb.setParameters(roomSize, damping, width, freeze, dry, wet);

	juVerb.process(buffer);
}
//==============================================================================

bool JUverbAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* JUverbAudioProcessor::createEditor()
{
    return new JUverbAudioProcessorEditor (*this);
}

void JUverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void JUverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JUverbAudioProcessor();
}

// Parameter Layout ==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout JUverbAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ROOM_SIZE", "Room Size", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DAMPING", "Damping", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WIDTH", "Width", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("FREEZE", "Freeze", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRY", "Dry", 0.0f, 100.0f, 100.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WET", "Wet", 0.0f, 100.0f, 50.0f));
    return { params.begin(), params.end() };
}