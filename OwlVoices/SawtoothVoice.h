
#pragma once
#include "JuceHeader.h"
#include "VSTComponents/Owl/VoiceModuleBuffered.h"
#include "VSTComponents/Owl/IVoiceModuleHost.h"
#include "VSTComponents/OwlDSP/DSPDelay.h"

class CSawtoothVoice : public CVoiceModuleBuffered
{
public:
	CSawtoothVoice(const std::string& name, IVoiceModuleHost& host, double detuneScale);

	void OnNoteStart(int midiNoteNumber, float velocity,
		SynthesiserSound*, int currentPitchWheelPosition) override;

	void OnNoteStop(float velocity, bool allowTailOff) override;

	void ProcessBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	// used to directly control frequency in LFO
	void SetSamplesPerCycle(int samples);

	void SetFrequencyModulator(IVoltageController* fm) { mFrequencyModulator = fm; }
private:
	virtual void InitProperties(CPropertiesRegistry & registry) override;

	double mCurrentSamplesPerCycle = 0;
	double mNextSamplesPerCycle = 0;
	double mSampleCounter = 0;
	double mDetune = 1;
	double mPortamento = 0.005;
	const double mDetuneScale = 1;
	CDSPDelay mDelay;
	IVoltageController* mFrequencyModulator = nullptr;
	// Inherited via CVoiceModuleBase

};