
#include "MixerVoice.h"
#include "VSTComponents/Owl/ProperiesRegistry.h"

CMixerVoice::CMixerVoice(const std::string& name, IVoiceModuleHost& host) : CVoiceModuleBuffered(name, host) {
    
}




void CMixerVoice::OnNoteStart(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
    for(auto& voice : GetModules()) {
        voice->OnNoteStart(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }
}

void CMixerVoice::OnNoteStop(float velocity, bool allowTailOff) {
    for(auto& voice : GetModules()) {
        voice->OnNoteStop(velocity,allowTailOff);
    }
}


bool CMixerVoice::IsBusy() const
{
	for (const auto& voice : GetModules()) {
		if (voice->IsBusy()) {
			return true;
		}
	}
	return false;
}


void CMixerVoice::ProcessBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples) {

	mBuffer.setSize(outputBuffer.getNumChannels(), outputBuffer.getNumSamples(), false, false, true);
	mBuffer.clear();

    for(auto& voice : GetModules()) {
        voice->ProcessBlockOfSound(mBuffer, startSample, numSamples);
    }
	
	
	outputBuffer.applyGain(startSample,numSamples,2 - mVolume);

	for (int i = 0; i < outputBuffer.getNumChannels(); i++) {
		outputBuffer.addFrom(i, startSample, mBuffer, i,startSample, numSamples, mVolume);
	}
	
}

void CMixerVoice::InitProperties(CPropertiesRegistry & registry)
{
	registry.AddProperty(GetPropName("Volume"), new CPropertyDouble01(mVolume, 0, 1));
	for (auto& voice : GetModules()) {
		voice->InitProperties(registry);
	}
}
