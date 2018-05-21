#pragma once

#define SAVE_FILE_ID "polypupPresets"

#define ATTACK_ID    "attack"
#define ATTACK_NAME  "attack"
#define ATTACK_LABEL "ms"
#define ATTACK_RANGE NormalisableRange<float>(1.0, 1000.0)
#define ATTACK_DEFAULT_VALUE 10.0

#define DECAY_ID    "decay"
#define DECAY_NAME  "decay"
#define DECAY_LABEL "ms"
#define DECAY_RANGE NormalisableRange<float>(1.0, 1000.0)
#define DECAY_DEFAULT_VALUE 10.0

#define SUSTAIN_ID    "sustain"
#define SUSTAIN_NAME  "sustain"
#define SUSTAIN_LABEL String()
#define SUSTAIN_RANGE NormalisableRange<float>(0.0, 1.0)
#define SUSTAIN_DEFAULT_VALUE 0.8

#define RELEASE_ID    "release"
#define RELEASE_NAME  "release"
#define RELEASE_LABEL "ms"
#define RELEASE_RANGE NormalisableRange<float>(0.0, 1000.0)
#define RELEASE_DEFAULT_VALUE 500.0

#define CUTOFF_ID    "cutoff"
#define CUTOFF_NAME  "cutoff"
#define CUTOFF_LABEL "ms"
#define CUTOFF_RANGE NormalisableRange<float>(10.0, 14000.0)
#define CUTOFF_DEFAULT_VALUE 14000.0

#define CUTOFF_ENVAMT_ID    "cutoff_envamt"
#define CUTOFF_ENVAMT_NAME  "cutoff_envamt"
#define CUTOFF_ENVAMT_LABEL ""
#define CUTOFF_ENVAMT_RANGE NormalisableRange<float>(-5000.0, 5000.0)
#define CUTOFF_ENVAMT_DEFAULT_VALUE 0.0

#define Q_ID    "q"
#define Q_NAME  "q"
#define Q_LABEL ""
#define Q_RANGE NormalisableRange<float>(1.0, 10.0)
#define Q_DEFAULT_VALUE 5.0

#include "../JuceLibraryCode/JuceHeader.h"
#include "JuceMaxiOsc.h"

class PolypupAudioProcessor  : public AudioProcessor
{
public:
    PolypupAudioProcessor();
    ~PolypupAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    Synthesiser synth;
    MidiKeyboardState keyboardState;
    AudioProcessorValueTreeState parameters;
    AudioDeviceManager audioDeviceManager;
    
    // envelope params
    double attack, decay, sustain, release;
    long holdTime;
    
    // filter params
    double filterCutoff, filterQ, filterEnvAmount;
    
private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolypupAudioProcessor)
};
