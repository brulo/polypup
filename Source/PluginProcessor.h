#pragma once

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
    
    // envelope params
    double attack, decay, sustain, release;
    long holdTime;
    
    // filter params
    double filterCutoff, filterQ, filterEnvAmount;
    
private:
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolypupAudioProcessor)
};
