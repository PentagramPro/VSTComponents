
#pragma once

#include "JuceHeader.h"
#include "ListenerRegistry.h"
#include "SynthState.h"
#include "ISynthStateManagerListener.h"

class CPropertiesRegistry;

class CSynthStateManager : public CListenerRegistry<ISynthStateManagerListener> {
public:
	CSynthStateManager(CPropertiesRegistry& propRegistry);
	virtual ~CSynthStateManager() {}

	void LoadStateFromFile(const std::string & filePath);
	void SaveStateToFile(const std::string & filePath);

	bool HasCurrentPath() const;
	const std::string& GetCurrentPath() const;

	void LoadStateFromMemory(const juce::MemoryBlock& state);
	void SaveStateToMemory(juce::MemoryBlock& state);

	void SetNameAndCategory(const std::string & name, const std::string & category);
	const CSynthState& GetState() const { return mState; }

private:
	CSynthState mState;
	std::string mCurrentPath;
	CPropertiesRegistry& mPropRegistry;
};