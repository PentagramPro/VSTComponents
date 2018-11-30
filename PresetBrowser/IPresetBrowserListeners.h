#pragma once
#include <string>

class IPresetBrowserListener {
public:
	virtual ~IPresetBrowserListener() {}
	virtual void OnLoadPreset(const std::string& filePath) = 0;
};