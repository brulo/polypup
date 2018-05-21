#include "FilterComponent.h"

FilterComponent::FilterComponent(AudioProcessorValueTreeState& valueTree, double *cutoff, double *q, double *envAmountCutoff, String cutoffId, String cutoffEnvAmtId, String qId)
{
    const Slider::SliderStyle sliderStyle = Slider::SliderStyle::LinearVertical;
    const int textBoxWidth = 50;
    const int textBoxHeight = 20;
    const bool showValueText = true;
    
    // cutoff label
    addAndMakeVisible(m_cutoffLabel);
    m_cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    m_cutoffLabel.setJustificationType(Justification::centred);
    
    // cutoff slider
    addAndMakeVisible(m_cutoffSlider);
    m_cutoffSlider.onValueChange = [this,cutoff] () mutable { *cutoff = m_cutoffSlider.getValue(); };
    m_cutoffAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTree, cutoffId, m_cutoffSlider));
    //m_cutoffSlider.setTextValueSuffix("");
    m_cutoffSlider.setNumDecimalPlacesToDisplay(2);
    m_cutoffSlider.setName("Cutoff");
    m_cutoffSlider.setSliderStyle(sliderStyle);
    m_cutoffSlider.setTextBoxStyle(showValueText ? Slider::TextBoxBelow : Slider::NoTextBox,
                                   true, textBoxWidth, textBoxHeight);
    
    // q label
    addAndMakeVisible(m_qLabel);
    m_qLabel.setText("Q", NotificationType::dontSendNotification);
    m_qLabel.setJustificationType(Justification::centred);
    
    // q slider
    addAndMakeVisible(m_qSlider);
    m_qSlider.onValueChange = [this,q] () mutable { *q = m_qSlider.getValue(); };
    m_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTree, qId, m_qSlider));
    m_qSlider.setNumDecimalPlacesToDisplay(2);
    m_qSlider.setName("Q");
    m_qSlider.setSliderStyle(sliderStyle);
    m_qSlider.setTextBoxStyle(showValueText ? Slider::TextBoxBelow : Slider::NoTextBox,
                                   true, textBoxWidth, textBoxHeight);
    
    // env amount label
    addAndMakeVisible(m_envAmountLabel);
    m_cutoffEnvAmountAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTree, cutoffEnvAmtId, m_envAmountSlider));
    m_envAmountLabel.setText("Env Amt", NotificationType::dontSendNotification);
    m_envAmountLabel.setJustificationType(Justification::centred);
    
    // env amount slider
    addAndMakeVisible(m_envAmountSlider);
    m_envAmountSlider.onValueChange = [this,envAmountCutoff] () mutable { *envAmountCutoff = m_envAmountSlider.getValue(); };
    m_cutoffEnvAmountAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTree, cutoffEnvAmtId, m_envAmountSlider));
    //m_envAmountSlider.setTextValueSuffix("");
    m_envAmountSlider.setNumDecimalPlacesToDisplay(2);
    m_envAmountSlider.setName("Env Amt");
    m_envAmountSlider.setSliderStyle(sliderStyle);
    m_envAmountSlider.setTextBoxStyle(showValueText ? Slider::TextBoxBelow : Slider::NoTextBox,
                                   true, textBoxWidth, textBoxHeight);
}

void FilterComponent::resized()
{
    auto boundsRect = getLocalBounds();
    const int labelHeight = 20;
    
    auto slice = boundsRect.removeFromRight(getWidth() * 0.33333);
    m_cutoffLabel.setBounds(slice.removeFromTop(labelHeight));
    m_cutoffSlider.setBounds(slice);
    
    slice = boundsRect.removeFromRight(getWidth() * 0.33333);
    m_qLabel.setBounds(slice.removeFromTop(labelHeight));
    m_qSlider.setBounds(slice);
    
    slice = boundsRect.removeFromRight(getWidth() * 0.33333);
    m_envAmountLabel.setBounds(slice.removeFromTop(labelHeight));
    m_envAmountSlider.setBounds(slice);
}
