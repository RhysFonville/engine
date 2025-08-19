#pragma once

#include <memory>
#include <string>
#include <expected>
#include <filesystem>
#include "../util/debug.h"

CREATE_ERROR_CATEGORY(asset_loader, {
	{1, "Could not open file"},
	{2, "Could not close file"},
	{3, "Not a valid file (does not exist or is not regular)"},
	{4, "Not a valid file (is not json)"},
	{5, "Could not parse json"},
})

class ENGINE_API IAssetLoader {
public:
	virtual ~IAssetLoader() = default;
	virtual std::expected<std::shared_ptr<void>, Error> load(const std::string& file) = 0;
};

template<typename T>
class ENGINE_API AssetLoader : public IAssetLoader {
public:
	virtual std::expected<std::shared_ptr<T>, Error> load_typed(const std::string& file) = 0;

	std::expected<std::shared_ptr<void>, Error> load(const std::string& file) override {
		if (!is_valid_file(file)) return std::unexpected{Error{3, asset_loader_category()}};
		return load_typed(file); // Implicitly upcasts
	}

protected:
	static bool is_valid_file(const std::string& file) noexcept {
		std::filesystem::path path{file};
		return std::filesystem::exists(path) &&
			std::filesystem::is_regular_file(path);
	}
};
