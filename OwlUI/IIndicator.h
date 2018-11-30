#pragma once

class CPropertiesRegistry;

class IIndicator {
public:
	virtual ~IIndicator() {}
	virtual void SetPropertiesRegistry(CPropertiesRegistry& properties) = 0;
};