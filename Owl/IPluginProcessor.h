#pragma once

class IVoiceModuleBase;
class CPropertiesRegistry;
class CSynthStateManager;

class IPluginProcessor {
public:
	virtual ~IPluginProcessor(){}

	virtual IVoiceModuleBase* GetModuleByName(const std::string& name) const = 0;
	virtual CPropertiesRegistry& GetPropertiesRegistry() = 0;
	virtual CSynthStateManager& GetSynthState() = 0;
};
