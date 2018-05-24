#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PresetManagerComponent.h"
#include "FilterComponent.h"
#include "ADSRComponent.h"
#include "OscillatorComponent.h"

/*
 TODO:
 
 - master gain slider
 - change default font
 - save/load presets
 - save/load previous AudioDeviceManager state
 - learn how to use LookAndFeel class
 - make slider textboxes wider
 - switch to responsive scaling design (instead of hardcoded pixel widths/heights)
 - noise oscillator
 */

class PolypupAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PolypupAudioProcessorEditor (PolypupAudioProcessor&, AudioProcessorValueTreeState&);
    ~PolypupAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    PolypupAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    PresetManagerComponent presetManagerComponent;
    AudioDeviceSelectorComponent audioDeviceSelectorComponent;
    OscillatorComponent oscillatorComponent;
    MidiKeyboardComponent keyboardComponent;
    FilterComponent filterComponent;
    ADSRComponent adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolypupAudioProcessorEditor)
};
