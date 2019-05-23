#pragma once

#include <vector>
#include <memory>


template<class T>
class CModuleRegistry {
public:
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

private:
	std::vector<std::unique_ptr<T>> mModules;
};