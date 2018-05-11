#include "FilterComponent.h"

FilterComponent::FilterComponent(double *cutoff, double *envAmountCutoff)
{
    const Slider::SliderStyle sliderStyle = Slider::SliderStyle::LinearVertical;
    const int textBoxWidth = 50;
    const int textBoxHeight = 20;
    const bool showValueText = false;
    
    // cutoff label
    addAndMakeVisible(m_cutoffLabel);
    m_cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    m_cutoffLabel.setJustificationType(Justification::centred);
    
    // cutoff slider
    addAndMakeVisible(m_cutoffSlider);
    m_cutoffSlider.setRange(10.0, 14000.0);
    //m_cutoffSlider.setTextValueSuffix("");
    m_cutoffSlider.setNumDecimalPlacesToDisplay(2);
    m_cutoffSlider.setName("Cutoff");
    m_cutoffSlider.setSliderStyle(sliderStyle);
    m_cutoffSlider.setTextBoxStyle(showValueText ? Slider::TextBoxBelow : Slider::NoTextBox,
                                   true, textBoxWidth, textBoxHeight);
    m_cutoffSlider.onValueChange = [this,cutoff] () mutable { *cutoff = m_cutoffSlider.getValue(); };
    m_cutoffSlider.setValue(1000.0);
    
    // env amount label
    addAndMakeVisible(m_envAmountLabel);
    m_envAmountLabel.setText("Env Amt", NotificationType::dontSendNotification);
    m_envAmountLabel.setJustificationType(Justification::centred);
    
    // env amount slider
    addAndMakeVisible(m_envAmountSlider);
    m_envAmountSlider.setRange(-10000.0, 10000.0);
    //m_cutoffSlider.setTextValueSuffix("");
    m_envAmountSlider.setNumDecimalPlacesToDisplay(2);
    m_envAmountSlider.setName("EnvAmt");
    m_envAmountSlider.setSliderStyle(sliderStyle);
    m_envAmountSlider.setTextBoxStyle(showValueText ? Slider::TextBoxBelow : Slider::NoTextBox,
                                   true, textBoxWidth, textBoxHeight);
    m_envAmountSlider.onValueChange = [this,envAmountCutoff] () mutable { *envAmountCutoff = m_envAmountSlider.getValue(); };
    m_envAmountSlider.setValue(0.0);
}

void FilterComponent::resized()
{
    auto boundsRect = getLocalBounds();
    const int labelHeight = 20;
    
    auto cutoffSlice = boundsRect.removeFromRight(getWidth() * 0.5);
    m_cutoffLabel.setBounds(cutoffSlice.removeFromTop(labelHeight));
    m_cutoffSlider.setBounds(cutoffSlice);
    
    m_envAmountLabel.setBounds(boundsRect.removeFromTop(labelHeight));
    m_envAmountSlider.setBounds(boundsRect);
}
