#pragma once
#include "JuceHeader.h"
#include "VSTComponents/Owl/VoiceModuleBuffered.h"
#include "VSTComponents/Owl/IVoiceModuleHost.h"

class CNoiseVoice : public CVoiceModuleBuffered {
public:
	CNoiseVoice(const std::string& name, IVoiceModuleHost& host)
		: CVoiceModuleBuffered(name, host) {}

	void OnNoteStart(int midiNoteNumber, float velocity,
		SynthesiserSound*, int currentPitchWheelPosition) override;

	void OnNoteStop(float velocity, bool allowTailOff) override;

	void ProcessBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	virtual void InitProperties(CPropertiesRegistry & registry) override;
private: 
	juce::Random mRandom;
};