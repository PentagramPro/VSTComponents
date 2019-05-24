#pragma once

#pragma once
#include "JuceHeader.h"
#include "VSTComponents/Owl/VoiceModuleBuffered.h"
#include "VSTComponents/Owl/IVoiceModuleHost.h"
#include "IVoltageController.h"


class CCVOne : public IVoltageController {
public:
	inline virtual float GetValue(int sampleNumber) const override { return 1; }
	static CCVOne instance;
};

class CCVZero : public IVoltageController {
public:
	inline virtual float GetValue(int sampleNumber) const override { return 0; }
	static CCVZero instance;
};

class CControlVoltageSource : public CVoiceModuleBuffered, public IVoltageController,
		public IVoiceModuleHost {
public:
	CControlVoltageSource(const std::string& name, IVoiceModuleHost& host, std::shared_ptr<CVoiceModuleBuffered> wrappedVoice, double initialValue);
	virtual ~CControlVoltageSource();
	void InitProperties(CPropertiesRegistry& registry) override;
	void OnNoteStart(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;

	void OnNoteStop(float velocity, bool allowTailOff) override;

	void ProcessBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

private:
	std::shared_ptr<CVoiceModuleBuffered> mWrappedVoice;
	AudioBuffer<float> mBuffer;

	// Inherited via IVoltageController
	inline virtual float GetValue(int sampleNumber) const override;

	// Inherited via IVoiceModuleHost
	virtual double GetSampleRate() const override;
	virtual void SoundEnded() override;
	double mInitialValue;
};

