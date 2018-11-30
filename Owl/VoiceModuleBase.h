#pragma once
#include "IVoiceModule.h"

class IVoiceModuleHost;

class CVoiceModuleBase : public IVoiceModule {
public:
	CVoiceModuleBase(const std::string& name, IVoiceModuleHost& host) : mName(name), mHost(&host) {}
	virtual ~CVoiceModuleBase() {}

	const std::string& GetName() const override { return mName; }
	virtual bool IsBusy() const override { return  mIsBusy; }

	void ReplaceHost(IVoiceModuleHost& host) { mHost = &host; }
	void ProcessBlockOfSound(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override final;

	using MutePredicate = std::function<bool(const IVoiceModule& m)>;
	void AddMuteRule(MutePredicate predicate);
	bool IsMute() const;

protected:
	virtual void ProcessBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) = 0;
	double GetSampleRate() const;
	std::string GetPropName(const std::string& propertyName) const;
	void StartSound();
	void StopSound();

private:
	std::vector<MutePredicate> mMuteRules;

	const std::string mName;
	IVoiceModuleHost * mHost;
	bool mIsBusy = false;
	
};