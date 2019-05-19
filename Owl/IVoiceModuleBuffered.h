#pragma once
#include "JuceHeader.h"
#include "IVoiceModuleBase.h"


class IVoiceModuleBuffered  {
public:
	virtual ~IVoiceModuleBuffered() {}
    virtual void ProcessBlockOfSound(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) = 0;
};