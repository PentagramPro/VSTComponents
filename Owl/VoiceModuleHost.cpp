

#include "VoiceModuleHost.h"
#include "VoiceModuleHostSound.h"

#include <string>
#include <chrono>

CVoiceModuleHost::CVoiceModuleHost(CPropertiesRegistry& propRegistry) : mPropRegistry(propRegistry) {

}

void CVoiceModuleHost::AddModule(CVoiceModuleBuffered* module) {
    CModuleRegistry::AddModule(module);
}

void CVoiceModuleHost::InitVoices()
{
	for (auto& voice : GetModules()) {
		voice->InitProperties(mPropRegistry);
	}
}




bool CVoiceModuleHost::canPlaySound(SynthesiserSound *sound) {
    auto voiceModuleSound = dynamic_cast<CVoiceModuleHostSound*> (sound);
    return voiceModuleSound!= nullptr;
}

void CVoiceModuleHost::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
	DBG("= New note " << midiNoteNumber << " (" << MidiMessage::getMidiNoteInHertz(midiNoteNumber) << ") =");
    for(auto& voice : GetModules()) {
        voice->OnNoteStart(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    }
}

void CVoiceModuleHost::stopNote(float velocity, bool allowTailOff) {
    for(auto& voice : GetModules()) {
        voice->OnNoteStop(velocity, allowTailOff);
    }
}

void CVoiceModuleHost::pitchWheelMoved(int newPitchWheelValue) {
    for(auto& voice : GetModules()) {

    }
}

void CVoiceModuleHost::controllerMoved(int controllerNumber, int newControllerValue) {
    for(auto& voice : GetModules()) {

    }
}

void CVoiceModuleHost::renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples) {
	auto start = std::chrono::high_resolution_clock::now();

    for(auto& voice : GetModules()) {
        voice->ProcessBlockOfSound(outputBuffer, startSample, numSamples);
    }

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;

	if (mDebugInfoCounter++ > 100) {
		mDebugInfoCounter = 0;
		DBG("Block render duration: " << elapsed.count() << ", max volume: " << outputBuffer.getMagnitude(startSample,numSamples));
		
	}
}

double CVoiceModuleHost::GetSampleRate() const {
    return getSampleRate();
}

void CVoiceModuleHost::SoundEnded() {
	for (auto& voice : GetModules()) {
		if (voice->IsBusy()) {
			return;
		}
	}
    clearCurrentNote();
}
/*
CVoiceModuleBuffered* CVoiceModuleHost::GetVoiceByName(const std::string & name) const
{
	auto res = std::find_if(GetModules().begin(), GetModules().end(), [&](const std::unique_ptr<CVoiceModuleBuffered>& m) {
		return m->GetName() == name;
	});

	if (res == GetModules().end()) {
		return nullptr;
	}
	return res->get();
}
*/