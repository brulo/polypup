#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PresetManagerComponent.h"
#include "FilterComponent.h"
#include "ADSRComponent.h"

/*
 TODO:
 
 - master gain slider
 - change default font
 - save/load presets
 - save/load previous AudioDeviceManager state
 - learn how to use LookAndFeel class
 - make slider textboxes wider
 - switch to responsive scaling design (instead of hardcoded pixel widths/heights)
 
 */

class PolypupAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PolypupAudioProcessorEditor (PolypupAudioProcessor&, AudioProcessorValueTreeState&);
    ~PolypupAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolypupAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    PresetManagerComponent presetManagerComponent;
    AudioDeviceSelectorComponent audioDeviceSelectorComponent;
    MidiKeyboardComponent keyboardComponent;
    FilterComponent filterComponent;
    ADSRComponent adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolypupAudioProcessorEditor)
};
