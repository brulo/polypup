#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolypupAudioProcessorEditor::PolypupAudioProcessorEditor(PolypupAudioProcessor& p, AudioProcessorValueTreeState& vts) :
    AudioProcessorEditor(&p),
    processor(p),
    valueTreeState(vts),
    presetManagerComponent(&p),
    audioDeviceSelectorComponent(processor.audioDeviceManager, 0, 0, 1, 2, true, false, false, false),
    oscillatorComponent(valueTreeState, &processor.oscType, OSC_TYPE_ID),
    keyboardComponent(processor.keyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard),
    filterComponent(valueTreeState, &processor.filterCutoff, &processor.filterQ, &processor.filterEnvAmount, CUTOFF_ID, CUTOFF_ENVAMT_ID, Q_ID),
    adsrComponent(valueTreeState, &processor.attack, &processor.decay, &processor.sustain, &processor.release, &processor.holdTime, ATTACK_ID, DECAY_ID, SUSTAIN_ID, RELEASE_ID)
{
    setSize(1024, 768);
    
    keyboardComponent.setKeyWidth(75);

    addAndMakeVisible(presetManagerComponent);
    addAndMakeVisible(audioDeviceSelectorComponent);
    addAndMakeVisible(oscillatorComponent);
    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(filterComponent);
    addAndMakeVisible(adsrComponent);
}

PolypupAudioProcessorEditor::~PolypupAudioProcessorEditor()
{
}

void PolypupAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PolypupAudioProcessorEditor::resized()
{
    auto boundsRect = getBounds();
    
    auto row = boundsRect.removeFromTop(25);
    presetManagerComponent.setBounds(row);
    
    row = boundsRect.removeFromTop(25);
    oscillatorComponent.setBounds(row);

    // audio device selector row
    //row = boundsRect.removeFromTop(300);
    //audioDeviceSelectorComponent.setBounds(row);
    
    // adsr and filter in a row
    row = boundsRect.removeFromTop(300);
    adsrComponent.setBounds(row.removeFromLeft(400));
    filterComponent.setBounds(row.removeFromLeft(200));
    
    boundsRect.removeFromTop(50);
    keyboardComponent.setBounds(boundsRect.removeFromTop(200));
}
