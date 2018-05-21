#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolypupAudioProcessorEditor::PolypupAudioProcessorEditor (PolypupAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), processor (p), valueTreeState(vts), keyboardComponent(processor.keyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard), filterComponent(valueTreeState, &processor.filterCutoff, &processor.filterQ, &processor.filterEnvAmount, CUTOFF_ID, CUTOFF_ENVAMT_ID, Q_ID), adsrComponent(valueTreeState, &processor.attack, &processor.decay, &processor.sustain, &processor.release, &processor.holdTime, ATTACK_ID, DECAY_ID, SUSTAIN_ID, RELEASE_ID)
{
    setSize (640, 480);
    keyboardComponent.setKeyWidth(75);
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
    
    auto row = boundsRect.removeFromTop(300);
    adsrComponent.setBounds(row.removeFromLeft(400));
    filterComponent.setBounds(row.removeFromLeft(200));
    
    boundsRect.removeFromTop(50);
    keyboardComponent.setBounds(boundsRect.removeFromTop(200));
}
