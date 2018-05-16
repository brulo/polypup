#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "FilterComponent.h"
#include "ADSRComponent.h"

class PolypupAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PolypupAudioProcessorEditor (PolypupAudioProcessor&);
    ~PolypupAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolypupAudioProcessor& processor;
    
    MidiKeyboardComponent keyboardComponent;
    FilterComponent filterComponent;
    ADSRComponent adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolypupAudioProcessorEditor)
};
