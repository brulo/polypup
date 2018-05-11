#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolypupAudioProcessorEditor::PolypupAudioProcessorEditor (PolypupAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), keyboardComponent(processor.keyboardState, MidiKeyboardComponent::Orientation::horizontalKeyboard)
{
    setSize (400, 300);
    addAndMakeVisible(keyboardComponent);
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
}
