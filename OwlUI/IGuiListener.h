#pragma once
#include <string>
class IGuiListener {
public:
	virtual ~IGuiListener() {}
	virtual void OnValueChanged(const std::string& name, float value) = 0;
	virtual void OnLoadPreset(const std::string& filePath) = 0;
	virtual void OnSavePreset(const std::string& name, const std::string& category) = 0;
};