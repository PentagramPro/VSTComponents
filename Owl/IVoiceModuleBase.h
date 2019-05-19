#pragma once
#include "JuceHeader.h"
class CPropertiesRegistry;


class IVoiceModuleBase {
public:
	virtual ~IVoiceModuleBase() {}
	virtual const std::string& GetName() const = 0;
	virtual void InitProperties(CPropertiesRegistry& registry) = 0;
	virtual void OnNoteStart(int midiNoteNumber, float velocity,
		juce::SynthesiserSound* sound, int currentPitchWheelPosition) = 0;
	virtual void OnNoteStop(float velocity, bool allowTailOff) = 0;
	virtual bool IsBusy() const = 0;
};