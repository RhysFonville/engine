#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "AssetLoader.h"

CREATE_ERROR_CATEGORY(asset_manager, {
    {1, "Cannot find loader for this asset type"}
})

class ENGINE_API AssetManager {
public:
	static std::expected<AssetManager, Error> init() noexcept;
	
	AssetManager(AssetManager&&) = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

	template<typename T>
	void register_loader(std::unique_ptr<AssetLoader<T>> loader) noexcept {
		loaders[typeid(T).hash_code()] = std::move(loader);
	}

	template<typename T>
	std::expected<std::shared_ptr<T>, Error> load(const std::string& filename) noexcept {
		auto type_id{typeid(T).hash_code()};

		// Cache lookup
		auto &type_cache{assets[type_id]};
		auto cached{type_cache.find(filename)};
		if (cached != type_cache.end()) {
			return std::static_pointer_cast<T>(cached->second.lock());
		}

		auto loader_it{loaders.find(type_id)};
		if (loader_it == loaders.end()) {
            return std::unexpected{Error{1, asset_manager_category()}};
		}

		// Load and cache
        std::expected<std::shared_ptr<void>, Error> loaded{loader_it->second->load(filename)};
        if (!loaded.has_value()) return std::unexpected{loaded.error()};

		type_cache[filename] = std::weak_ptr{loaded.value()};
		return std::static_pointer_cast<T>(loaded.value());
	}

private:
	AssetManager() noexcept : loaders{}, assets{} {}

	std::unordered_map<size_t, std::unique_ptr<IAssetLoader>> loaders;
	std::unordered_map<size_t, std::unordered_map<std::string, std::weak_ptr<void>>> assets;
};

