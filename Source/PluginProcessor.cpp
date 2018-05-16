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
//, m_osc(*attack, *decay, *sustain, *release)
{
    auto numVoices = 8;
    
    // Add some voices...
    for (auto i = 0; i < numVoices; ++i)
        synth.addVoice (new JuceMaxiOscVoice(JuceMaxiOscType::Saw, &attack, &decay, &sustain, &release, &holdTime, &filterCutoff, &filterEnvAmount));
    
    // ..and give the synth a sound to play
    synth.addSound (new JuceMaxiOscSound());
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
    synth.setCurrentPlaybackSampleRate (sampleRate);
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
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    /*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
     */
}

//==============================================================================
bool PolypupAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PolypupAudioProcessor::createEditor()
{
    return new PolypupAudioProcessorEditor (*this);
}

//==============================================================================
void PolypupAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PolypupAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolypupAudioProcessor();
}
