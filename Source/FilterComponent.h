#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FilterComponent : public Component
{
public:
    FilterComponent(double *cutoff, double * q, double *envAmountCutoff);
    //~ADSRComponent();
    
    void resized() override;
    
private:
    Slider m_cutoffSlider, m_envAmountSlider, m_qSlider;
    Label  m_cutoffLabel, m_envAmountLabel, m_qLabel;
};
