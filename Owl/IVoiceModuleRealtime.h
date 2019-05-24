#pragma once

class IVoiceModuleBase;


class IVoiceModuleRealtime  {
public:
	virtual ~IVoiceModuleRealtime() {}
	virtual void ProcessSample(int channel, float& sample, int sampleNumber) = 0;
	virtual void OnNextDataBuffer(int channelsCount, int samplesCount) {}
	virtual IVoiceModuleBase& GetBase() = 0;
};
