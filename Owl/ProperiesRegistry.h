#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "JuceHeader.h"
#include "ListenerRegistry.h"
#include "Toolbox.h"
#include <functional>

class CSynthState;

class IPropertyRecord {
public:
	virtual ~IPropertyRecord() {}
	virtual void SetReference(float value) = 0;
	virtual float GetFromReference() = 0;
	virtual void SetRaw(double value) = 0;
	virtual double GetRaw() const = 0;
	virtual void SetMinValue() = 0;
};

template<typename T>
class CPropertyRecord : public IPropertyRecord {
public:
	void SetMinValue() override{
		mReference = mMinValue;
	}
protected:
	CPropertyRecord(T& reference, T min, T max) : mReference(reference), mMinValue(min), mMaxValue(max) {}

	T & mReference;
	T mMinValue;
	T mMaxValue;

};

class CPropertyDouble01 : public CPropertyRecord<double>{
public:
	CPropertyDouble01(double& reference, double min, double max) : CPropertyRecord<double>(reference, min, max) { }

	virtual void SetReference(float value) override {
		double convertedVal = Toolbox::clamp((double)value, 0.0, 1.0);
		mReference = mMinValue + (mMaxValue - mMinValue)*convertedVal;

	}

	virtual float GetFromReference() override {
		return (mReference - mMinValue) / (mMaxValue-mMinValue);
	}

	virtual void SetRaw(double value) override {
		mReference = value;
	}

	virtual double GetRaw() const override {
		return mReference;
	}

};

class CPropertySquareDouble01 : public CPropertyDouble01 {
public:
	CPropertySquareDouble01(double& reference, double min, double max) : CPropertyDouble01(reference, min, max) { }

	virtual void SetReference(float value) override {
		CPropertyDouble01::SetReference(value*value);
	}

	virtual float GetFromReference() override {
		return std::sqrt(CPropertyDouble01::GetFromReference());
	}

};

class CPropertyInt : public CPropertyRecord<int> {
public:
	CPropertyInt(int& reference, int min, int max) : CPropertyRecord<int>(reference, min, max) { }

	virtual void SetReference(float value) override {
		mReference = Toolbox::clamp((int)std::lround(value), mMinValue, mMaxValue);
	}

	virtual float GetFromReference() override {
		return mReference;
	}

	virtual void SetRaw(double value) override {
		mReference = std::round(value);
	}

	virtual double GetRaw() const override {
		return mReference;
	}

};

class CPropertiesList : public IPropertyRecord {
public:
	CPropertiesList(IPropertyRecord* firstProperty, bool storeOnDisk) {
		AddProperty(firstProperty, storeOnDisk);
	}

	void AddProperty(IPropertyRecord* prop, bool storeOnDisk) {
		mProperties.emplace_back(prop);
		if (storeOnDisk) {
			mStoreOnDisk = storeOnDisk;
		}
	}

	virtual void SetReference(float value) {
		for (auto& item : mProperties) {
			item->SetReference(value);
		}
	}
	virtual float GetFromReference() {
		const float res = mProperties.front()->GetFromReference();
		if (std::isnan(res))
			return 0;
		return res;
	}
	virtual void SetRaw(double value) {
		for (auto& item : mProperties) {
			item->SetRaw(value);
		}
	}

	void SetMinValue() {
        for (auto& item : mProperties) {
            item->SetMinValue();
        }
	}
 	virtual double GetRaw() const {
		return mProperties.front()->GetRaw();
	}

	bool IsStoreOnDisk() const { return mStoreOnDisk; }
private:
	std::vector<std::unique_ptr<IPropertyRecord>> mProperties;
	bool mStoreOnDisk = false;
};

class IPropertiesRegistryListener {
public:
	virtual ~IPropertiesRegistryListener() {}
	virtual void OnPropertiesFromSynthState() = 0;
};

class CPropertiesRegistry : public CListenerRegistry<IPropertiesRegistryListener> {
public:

	void SetProperty(const std::string& name, float value);
	void ForceProperty(const std::string& name, float value);

	void FromSynthState(const CSynthState& state);
	void ToSynthState(CSynthState& state);

	
	float GetPropertyValueFromReference(const std::string& name) const {
		auto p = mProperties.find(name);
		if (p != mProperties.end()) {
			return p->second->GetFromReference();
		}
		return 0;
	}

	float GetPropertyValueRaw(const std::string& name) const {
		auto p = mProperties.find(name);
		if (p != mProperties.end()) {
			return p->second->GetRaw();
		}
		return 0;
	}

	
	void AddProperty(const std::string & name, IPropertyRecord* prop, bool storeOnDisk = true);


	bool HasProperty(const std::string & name) const;
private:
	std::unordered_map<std::string, std::unique_ptr<CPropertiesList>> mProperties;
	std::unordered_map<std::string, float> mForcedProperties;
};