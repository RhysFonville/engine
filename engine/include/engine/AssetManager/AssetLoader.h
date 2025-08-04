#pragma once

#include <memory>
#include <string>

class IAssetLoader {
public:
    virtual ~IAssetLoader() = default;
	virtual std::shared_ptr<void> load(const std::string& filename) = 0;
};

template<typename T>
class AssetLoader : public IAssetLoader {
public:
	virtual std::shared_ptr<T> load_typed(const std::string& filename) = 0;

	std::shared_ptr<void> load(const std::string& filename) override {
		return load_typed(filename); // Implicitly upcasts
	}
};
