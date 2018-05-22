#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class PresetManagerComponent : public Component
{
public:
    PresetManagerComponent(PolypupAudioProcessor* processor);

    void resized() override;
    
private:
    //Slider m_cutoffSlider;
    //Label  m_cutoffLabel;
    ComboBox m_comboBox;
    TextButton m_saveButton, m_loadButton;

    
    //std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_cutoffAttachment;
};
