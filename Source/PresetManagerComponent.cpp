#include "PresetManagerComponent.h"

PresetManagerComponent::PresetManagerComponent(PolypupAudioProcessor* processor)
{
    addAndMakeVisible(m_saveButton);
    addAndMakeVisible(m_loadButton);
    addAndMakeVisible(m_comboBox);
    
    m_saveButton.onClick = [this, processor] { processor->save(); };
    m_loadButton.onClick = [this, processor] { processor->load(); };
}

void PresetManagerComponent::resized()
{
    auto boundsRect = getLocalBounds();
    m_saveButton.setBounds(boundsRect.removeFromRight(100));
    m_loadButton.setBounds(boundsRect.removeFromRight(100));
    m_comboBox.setBounds(boundsRect);
}
