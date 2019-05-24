#pragma once

class IVoiceModuleBase;


class IVoiceModuleRealtime  {
public:
	virtual ~IVoiceModuleRealtime() {}
	virtual void ProcessSample(int channel, float& sample, int sampleNumber) = 0;
	virtual void OnNextDataBuffer(int channelNum) {}
	virtual IVoiceModuleBase& GetBase() = 0;
};
