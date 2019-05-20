#pragma once
#include "JuceHeader.h"
#include "IVoiceModuleBase.h"


class IVoiceModuleRealtime  {
public:
	virtual ~IVoiceModuleRealtime() {}
	virtual void ProcessSample(int channel, double& sample) = 0;
	virtual void SetChannelNumber(int channelNum) {}
};