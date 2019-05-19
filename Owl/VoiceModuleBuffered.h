#pragma once

#include "IVoiceModuleBuffered.h"
#include "VoiceModuleBase.h"

class CVoiceModuleBuffered : public CVoiceModuleBase, public IVoiceModuleBuffered {
public:
	virtual ~CVoiceModuleBuffered() {}
	CVoiceModuleBuffered(const std::string& name, IVoiceModuleHost& host) : CVoiceModuleBase(name, host) {}

	virtual void ProcessBlockOfSound(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) {
		if (IsMute()) {
			return;
		}
		ProcessBlock(outputBuffer, startSample, numSamples);
	}

protected:
	virtual void ProcessBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) = 0;

};