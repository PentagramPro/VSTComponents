#pragma once
#include "JuceHeader.h"
#include "IVoiceModule.h"
#include "VoiceModuleBase.h"
#include "IVoiceModuleHost.h"

class CPropertiesRegistry;

class CVoiceModuleHost : public juce::SynthesiserVoice, public IVoiceModuleHost {
public:
    CVoiceModuleHost(CPropertiesRegistry& propRegistry);
    void AddModule(IVoiceModule* module);
	template<class T>
	T& AddModule(T* module) {
		AddModule((IVoiceModule*)module);
		return *module;
	}

    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity,
		juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;


    double GetSampleRate() const override;

    void SoundEnded() override;

	IVoiceModule* GetVoiceByName(const std::string& name) const ;

private:
    std::vector<std::unique_ptr<IVoiceModule>> mVoiceModules;
	CPropertiesRegistry & mPropRegistry;
};