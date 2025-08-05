#pragma once

#include <memory>
#include <string>
#include <expected>
#include "../util/debug.h"

CREATE_ERROR_CATEGORY(asset_loader, {
    {1, "Could not open file"},
    {2, "Could not close file"}
})

class IAssetLoader {
public:
    virtual ~IAssetLoader() = default;
	virtual std::expected<std::shared_ptr<void>, Error> load(const std::string& filename) = 0;
};

template<typename T>
class AssetLoader : public IAssetLoader {
public:
	virtual std::expected<std::shared_ptr<T>, Error> load_typed(const std::string& filename) = 0;

    std::expected<std::shared_ptr<void>, Error> load(const std::string& filename) override {
        log("load");
		return load_typed(filename); // Implicitly upcasts
	}
};

