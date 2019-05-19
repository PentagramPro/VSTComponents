#pragma once
#include "IVoiceModuleBase.h"

class IVoiceModuleHost;

class CVoiceModuleBase : public IVoiceModuleBase {
public:
	CVoiceModuleBase(const std::string& name, IVoiceModuleHost& host) : mName(name), mHost(&host) {}
	virtual ~CVoiceModuleBase() {}

	const std::string& GetName() const override { return mName; }
	virtual bool IsBusy() const override { return  mIsBusy; }

	void ReplaceHost(IVoiceModuleHost& host) { mHost = &host; }

	using MutePredicate = std::function<bool(const IVoiceModuleBase& m)>;
	void AddMuteRule(MutePredicate predicate);
	bool IsMute() const;

protected:
	
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