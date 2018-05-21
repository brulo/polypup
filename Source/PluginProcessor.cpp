#include "PluginProcessor.h"
#include "PluginEditor.h"

PolypupAudioProcessor::PolypupAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
, parameters(*this, nullptr),
audioDeviceManager()
{
    // set up parameters
    // ADSR env
    parameters.createAndAddParameter(ATTACK_ID, ATTACK_NAME, ATTACK_LABEL, ATTACK_RANGE, ATTACK_DEFAULT_VALUE, nullptr, nullptr);
    parameters.createAndAddParameter(DECAY_ID, DECAY_NAME, DECAY_LABEL, DECAY_RANGE, DECAY_DEFAULT_VALUE, nullptr, nullptr);
    parameters.createAndAddParameter(SUSTAIN_ID, SUSTAIN_NAME, SUSTAIN_LABEL, SUSTAIN_RANGE, SUSTAIN_DEFAULT_VALUE, nullptr, nullptr);
    parameters.createAndAddParameter(RELEASE_ID, RELEASE_NAME, RELEASE_LABEL, RELEASE_RANGE, RELEASE_DEFAULT_VALUE, nullptr, nullptr);
    
    // filter
    parameters.createAndAddParameter(CUTOFF_ENVAMT_ID, CUTOFF_ENVAMT_NAME, CUTOFF_ENVAMT_LABEL, CUTOFF_ENVAMT_RANGE, CUTOFF_ENVAMT_DEFAULT_VALUE, nullptr, nullptr);
    parameters.createAndAddParameter(CUTOFF_ID, CUTOFF_NAME, CUTOFF_LABEL, CUTOFF_RANGE, CUTOFF_DEFAULT_VALUE, nullptr, nullptr);
    parameters.createAndAddParameter(Q_ID, Q_NAME, Q_LABEL, Q_RANGE, Q_DEFAULT_VALUE, nullptr, nullptr);
    
    parameters.state = ValueTree(Identifier(SAVE_FILE_ID));
    
    // set up the synth
    auto numVoices = 8;
    for(auto i = 0; i < numVoices; ++i)
    {
        synth.addVoice (new JuceMaxiOscVoice(JuceMaxiOscType::Saw, &attack, &decay, &sustain, &release, &holdTime, &filterCutoff, &filterQ, &filterEnvAmount));
    }
    synth.addSound(new JuceMaxiOscSound());
}

PolypupAudioProcessor::~PolypupAudioProcessor()
{
}

const String PolypupAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolypupAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolypupAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PolypupAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PolypupAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolypupAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolypupAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolypupAudioProcessor::setCurrentProgram (int index)
{
}

const String PolypupAudioProcessor::getProgramName (int index)
{
    return {};
}

void PolypupAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PolypupAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    keyboardState.reset();
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void PolypupAudioProcessor::releaseResources()
{
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolypupAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PolypupAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    auto numSamples = buffer.getNumSamples();
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

    buffer.applyGain(Decibels::decibelsToGain(-20.0));
}

//==============================================================================
bool PolypupAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PolypupAudioProcessor::createEditor()
{
    return new PolypupAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void PolypupAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    ScopedPointer<XmlElement> xml(parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PolypupAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    /*
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if(xml != nullptr)
    {
        if(xml->hasTagName(SAVE_FILE_ID))
        {
            parametersValueTree.state = ValueTree::fromXml(*xml);
        }
    }
     */
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.replaceState (ValueTree::fromXml (*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolypupAudioProcessor();
}
