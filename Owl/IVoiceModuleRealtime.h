#pragma once
#include "JuceHeader.h"
#include "IVoiceModuleBase.h"


class IVoiceModuleRealtime  {
public:
	virtual ~IVoiceModuleRealtime() {}
	virtual void ProcessSample(int channel, float& sample) = 0;
	virtual void SetChannelNumber(int channelNum) {}
	virtual IVoiceModuleBase& GetBase() = 0;
};