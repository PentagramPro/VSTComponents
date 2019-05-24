#pragma once
#include "JuceHeader.h"
#include "VSTComponents/Owl/VoiceModuleBuffered.h"
#include "VSTComponents/Owl/IVoiceModuleRealtime.h"

class IVoiceModuleHost;


class EnvelopeVoice  : public CVoiceModuleBuffered, public IVoiceModuleRealtime {
public:
	EnvelopeVoice(const std::string& name, IVoiceModuleHost& host) : CVoiceModuleBuffered(name, host) {}

	void InitProperties(CPropertiesRegistry& registry) override;
    void OnNoteStart(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
	
    void OnNoteStop(float velocity, bool allowTailOff) override;

    void ProcessBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

	virtual void ProcessSample(int channel, float& sample, int sampleNumber) override;
	virtual void OnNextDataBuffer(int channelNum, int samplesCount) override;
	virtual IVoiceModuleBase& GetBase() override {return *this;}

private:
    enum class EState {Idle, Attack, Decay, Sustain, Release};
	struct SContext{
		bool hasDecay;
		double maxAttack;
		double attackSamples;
		double decaySamples;
	};

    double mAttackTime = 1;
	double mDecayTime = 0;
	double mReleaseTime = 1;
	double mSustainLevel = 1;
	int mRetrigger = 1;
    double mSoundLevel = 0;

	double mReleaseStep = 1;
    EState mState = EState ::Idle;
    SContext mContext;
};


