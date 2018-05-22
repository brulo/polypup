/*
  ==============================================================================

    ParameterDefines.h
    Created: 20 May 2018 9:15:56pm
    Author:  brulo

  ==============================================================================
*/

#pragma once

#define SAVE_FILE_ID "polypupPresets"

#define ATTACK_ID    "attack"
#define ATTACK_NAME  "attack"
#define ATTACK_LABEL "ms"
#define ATTACK_RANGE NormalisableRange<float>(1.0, 1000.0)
#define ATTACK_DEFAULT_VALUE 10.0

#define DECAY_ID    "decay"
#define DECAY_NAME  "decay"
#define DECAY_LABEL "ms"
#define DECAY_RANGE NormalisableRange<float>(1.0, 1000.0)
#define DECAY_DEFAULT_VALUE 10.0

#define SUSTAIN_ID    "sustain"
#define SUSTAIN_NAME  "sustain"
#define SUSTAIN_LABEL String()
#define SUSTAIN_RANGE NormalisableRange<float>(0.0, 1.0)
#define SUSTAIN_DEFAULT_VALUE 0.8

#define RELEASE_ID    "release"
#define RELEASE_NAME  "release"
#define RELEASE_LABEL "ms"
#define RELEASE_RANGE NormalisableRange<float>(0.0, 1000.0)
#define RELEASE_DEFAULT_VALUE 500.0

#define CUTOFF_ID    "cutoff"
#define CUTOFF_NAME  "cutoff"
#define CUTOFF_LABEL "ms"
#define CUTOFF_RANGE NormalisableRange<float>(10.0, 14000.0)
#define CUTOFF_DEFAULT_VALUE 14000.0

#define CUTOFF_ENVAMT_ID    "cutoff_envamt"
#define CUTOFF_ENVAMT_NAME  "cutoff_envamt"
#define CUTOFF_ENVAMT_LABEL ""
#define CUTOFF_ENVAMT_RANGE NormalisableRange<float>(-5000.0, 5000.0)
#define CUTOFF_ENVAMT_DEFAULT_VALUE 0.0

#define Q_ID    "q"
#define Q_NAME  "q"
#define Q_LABEL ""
#define Q_RANGE NormalisableRange<float>(1.0, 10.0)
#define Q_DEFAULT_VALUE 5.0
