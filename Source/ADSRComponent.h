#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Maximilian/maximilian.h"

class ADSRComponent : public Component
{
public:
    ADSRComponent(AudioProcessorValueTreeState& valueTree, double *attack, double *decay, double *sustain, double *release, long *holdTime, String attackId, String decayId, String sustainId, String releaseId);
    
    void resized() override;
    
private:
    Slider m_attackSlider, m_decaySlider, m_sustainSlider, m_releaseSlider;
    Label  m_attackLabel,  m_decayLabel,  m_sustainLabel,  m_releaseLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_attackAttachment, m_decayAttachment, m_sustainAttachment, m_releaseAttachment;
};
