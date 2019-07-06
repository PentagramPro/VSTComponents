#pragma once

#include <vector>
#include <memory>
#include "IVoiceModuleBase.h"

class IModuleRegistry {
public:
	virtual ~IModuleRegistry() {}
	virtual IVoiceModuleBase* FindModuleByName(const std::string& name) = 0;
};

template<class T>
class CModuleRegistry : public IModuleRegistry {
public:
	virtual ~CModuleRegistry() {}

	virtual void AddModule(T* voice) {
		mModules.emplace_back(voice);
	}
	template<class M>
	M& AddModule(M* module) {

		static_assert(std::is_base_of<T, M>::value);
		AddModule((T*)module);
		return *module;
	}

	std::vector<std::unique_ptr<T>>& GetModules() {
		return mModules;
	}

	const std::vector<std::unique_ptr<T>>& GetModules() const {
		return mModules;
	}

	IVoiceModuleBase* FindModuleByName(const std::string& name) override {
		for (const auto& m : GetModules()) {

			IVoiceModuleBase* voiceModule = dynamic_cast<IVoiceModuleBase*>(m.get());
			if (voiceModule && name == voiceModule->GetName()) {
				return voiceModule;
			}

			IModuleRegistry* registry = dynamic_cast<IModuleRegistry*>(m.get());
			if (registry) {
				voiceModule = registry->FindModuleByName(name);
				if (voiceModule) {
					return voiceModule;
				}
			}

		}
		return nullptr;
	}

private:
	std::vector<std::unique_ptr<T>> mModules;
};