#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FilterComponent : public Component
{
public:
    FilterComponent(AudioProcessorValueTreeState& valueTree, double *cutoff, double * q, double *envAmountCutoff, String cutoffId, String cutoffEnvAmtId, String qId);
    
    void resized() override;
    
private:
    Slider m_cutoffSlider, m_envAmountSlider, m_qSlider;
    Label  m_cutoffLabel, m_envAmountLabel, m_qLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_cutoffAttachment, m_cutoffEnvAmountAttachment, m_qAttachment;
};
