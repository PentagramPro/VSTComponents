#include "EnvelopeVoice.h"
#include "VSTComponents/Owl/ProperiesRegistry.h"
#include <algorithm>
#include <string>
#include <cmath>

const double MaxVolume = 1.0;
const double MinDecay = 0.01;

void EnvelopeVoice::InitProperties(CPropertiesRegistry & registry)
{
	registry.AddProperty(GetPropName("Attack"), new CPropertySquareDouble01(mAttackTime, 0.0004, 5.0));
	registry.AddProperty(GetPropName("Decay"), new CPropertySquareDouble01(mDecayTime, 0.001, 3.0));
	registry.AddProperty(GetPropName("Release"), new CPropertySquareDouble01(mReleaseTime, 0.001, 10.0));
	registry.AddProperty(GetPropName("Sustain"), new CPropertyDouble01(mSustainLevel, 0.0, 1.0));
	registry.AddProperty(GetPropName("Retrigger"), new CPropertyInt(mRetrigger, 0, 1));
}

void EnvelopeVoice::OnNoteStart(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
    //mSoundLevel = 0;

	mState = EState::Attack;
	if (mRetrigger == 1) {
		mSoundLevel = 0;
	}
	StartSound();
}

void EnvelopeVoice::OnNoteStop(float velocity, bool allowTailOff) {
    mState = EState::Release;
	const double sampleRate = GetSampleRate();
	if (sampleRate > 0) {
		mReleaseStep = mSoundLevel / (sampleRate*mReleaseTime);
	}
	else {
		mReleaseStep = 1;
	}
}



void EnvelopeVoice::ProcessBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    int samplesCount = numSamples;
    int currentSample = startSample;

	OnNextDataBuffer(outputBuffer.getNumChannels(), outputBuffer.getNumSamples());

    while (--samplesCount >= 0){

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;) {
			ProcessSample(i, *outputBuffer.getWritePointer(i, currentSample), currentSample);
        }
        currentSample++;
    }
}

void EnvelopeVoice::ProcessSample(int channel, float& sample, int sampleNumber){
	if(channel==0) {
		if (mState == EState::Attack) {
			mSoundLevel += mContext.attackSamples;
			if (mSoundLevel > mContext.maxAttack) {
				mSoundLevel = mContext.maxAttack;
				mState = mContext.hasDecay ? EState::Decay : EState::Sustain;
			}
		} else if (mState == EState::Decay) {
			mSoundLevel -= mContext.decaySamples;
			if (mSoundLevel < mSustainLevel) {
				mSoundLevel = mSustainLevel;
				mState = EState::Sustain;
			}
		} else if (mState == EState::Release) {
			mSoundLevel -= mReleaseStep;
			if (mSoundLevel <= 0) {
				mSoundLevel = 0;
				mState = EState::Idle;
				StopSound();
			}
		} else if (mState == EState::Idle) {
			mSoundLevel = 0;
		} else {
			mSoundLevel = mSustainLevel;
		}
	}
	sample*=mSoundLevel;
}
void EnvelopeVoice::OnNextDataBuffer(int channelNum, int samplesCount) {
	mContext.hasDecay = mDecayTime > MinDecay;
	mContext.maxAttack = mContext.hasDecay ? MaxVolume : mSustainLevel;
	mContext.attackSamples = mContext.maxAttack / (GetSampleRate()*mAttackTime);
	mContext.decaySamples = mContext.hasDecay ? (mContext.maxAttack-mSustainLevel) / (GetSampleRate()*mDecayTime) : 0;

}

