#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JuceMaxiOsc.h"

class OscillatorComponent : public Component
{
public:
    OscillatorComponent(AudioProcessorValueTreeState& valueTree, JuceMaxiOscType *oscType, String oscTypeId);
    
    void resized() override;
    
private:
    
    Label  m_oscTypeLabel;
    ComboBox m_oscTypeComboBox;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> m_oscTypeAttachment;
};
