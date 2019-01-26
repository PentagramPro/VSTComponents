#pragma once
#include <string>
class IGuiListener {
public:
	virtual ~IGuiListener() {}
	virtual void OnValueChanged(const std::string& name, float value) = 0;
};