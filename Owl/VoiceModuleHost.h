#pragma once
#include "JuceHeader.h"
#include "IVoiceModuleBuffered.h"
#include "VoiceModuleBase.h"
#include "IVoiceModuleHost.h"

#include "ModuleRegistry.h"

class CPropertiesRegistry;

class CVoiceModuleHost : public juce::SynthesiserVoice, public IVoiceModuleHost, public CModuleRegistry<CVoiceModuleBuffered> {
public:
    CVoiceModuleHost(CPropertiesRegistry& propRegistry);
    
	virtual void AddModule(CVoiceModuleBuffered* voice) override;
	void InitVoices();
    

    double GetSampleRate() const override;

    void SoundEnded() override;

	//CVoiceModuleBuffered* GetVoiceByName(const std::string& name) const ;

private:
	bool canPlaySound(juce::SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity,
		juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

	CPropertiesRegistry & mPropRegistry;
	int mDebugInfoCounter = 0;
};