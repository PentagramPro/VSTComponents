
#pragma once
#include "JuceHeader.h"
#include <unordered_map>
#include <string>

struct StateInfo {
	std::string category = "Default";
	std::string name = "Default";
};

class CSynthState {
public:
	CSynthState();
	
	void Deserialize(const char* data, int size);
	void Serialize(juce::MemoryBlock& destData);

	void AddKeyValue(const std::string& key, double value);
	const std::unordered_map<std::string, double>& GetState() const { return mState; }
	const StateInfo& GetStateInfo() const {return mStateInfo; }

	static StateInfo GetStateInfoFromData(const char* data, int size);
	void SetNameAndCategory(const std::string& name, const std::string& category);
private:
	
	std::unordered_map<std::string, double> mState;
	StateInfo mStateInfo;
};