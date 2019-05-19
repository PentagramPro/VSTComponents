#pragma once
#include "JuceHeader.h"
#include "IVoiceModuleBase.h"


class IVoiceModuleRealtime  {
public:
	virtual ~IVoiceModuleRealtime() {}
	virtual void ProcessSample(double& sample) = 0;
};