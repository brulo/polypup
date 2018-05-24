#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(AudioProcessorValueTreeState& valueTree, JuceMaxiOscType *oscType, String oscTypeId) : m_oscTypeComboBox("oscCombo")
{
    // osc type
    m_oscTypeComboBox.addItem("Triangle", JuceMaxiOscType::Tri);
    m_oscTypeComboBox.addItem("Sin", JuceMaxiOscType::Sin);
    m_oscTypeComboBox.addItem("Saw", JuceMaxiOscType::Saw);
    m_oscTypeComboBox.addItem("Square", JuceMaxiOscType::Square);
    addAndMakeVisible(m_oscTypeComboBox);
    m_oscTypeComboBox.onChange = [this, oscType] () mutable { *oscType = (JuceMaxiOscType)m_oscTypeComboBox.getSelectedId(); };
    m_oscTypeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTree, oscTypeId, m_oscTypeComboBox));
}

void OscillatorComponent::resized()
{
    m_oscTypeComboBox.setBounds(getLocalBounds());
}
