#pragma once
#include "JuceHeader.h"
#include <vector>
#include "VSTComponents/Owl/VoiceModuleBuffered.h"
#include "VSTComponents/Owl/IVoiceModuleHost.h"
#include "VSTComponents/Owl/ModuleRegistry.h"

class CMixerVoice : public CVoiceModuleBuffered, public CModuleRegistry<CVoiceModuleBuffered> {

public:
    CMixerVoice(const std::string& name, IVoiceModuleHost& host);

    void OnNoteStart(int midiNoteNumber, float velocity,
            SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void OnNoteStop(float velocity, bool allowTailOff) override;
	

	virtual bool IsBusy() const override;

    void ProcessBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
private:
    
	AudioBuffer<float> mBuffer;

	// Inherited via CVoiceModuleBase
	virtual void InitProperties(CPropertiesRegistry & registry) override;
	double mVolume = 1;
};

