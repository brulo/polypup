#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolypupAudioProcessorEditor::PolypupAudioProcessorEditor (PolypupAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), keyboardComponent(processor.keyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard),  filterComponent(&processor.filterCutoff, &processor.filterQ, &processor.filterEnvAmount), adsrComponent(&processor.attack, &processor.decay, &processor.sustain, &processor.release, &processor.holdTime)
{
    setSize (400, 300);
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

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PolypupAudioProcessorEditor::resized()
{
    auto boundsRect = getBounds();
    
    keyboardComponent.setBounds(boundsRect.removeFromTop(50));
    
    auto row = boundsRect.removeFromTop(150);
    adsrComponent.setBounds(row.removeFromLeft(400));
    filterComponent.setBounds(row.removeFromLeft(200));
     
}
