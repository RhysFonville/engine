#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "AssetLoader.h"

class AssetManager {
public:
	AssetManager(AssetManager& other) = delete;
	void operator=(const AssetManager&) = delete;
	static AssetManager* get_instance() noexcept;

	template<typename T>
	void register_loader(std::unique_ptr<AssetLoader<T>> loader) noexcept {
		loaders[typeid(T).hash_code()] = std::move(loader);
	}

	template<typename T>
	std::shared_ptr<T> load(const std::string& filename) noexcept {
		auto type_id{typeid(T).hash_code()};

		// Cache lookup
		auto &type_cache{assets[type_id]};
		auto cached{type_cache.find(filename)};
		if (cached != type_cache.end()) {
			return std::static_pointer_cast<T>(cached->second.lock());
		}

		auto loader_it{loaders.find(type_id)};
		if (loader_it == loaders.end()) {
			//throw std::runtime_error("No loader registered for this asset type");
		}

		// Load and cache
		auto loaded{loader_it->second->load(filename)};
		type_cache[filename] = std::weak_ptr{loaded};
		return std::static_pointer_cast<T>(loaded);
	}

private:
	AssetManager();
	static AssetManager* asset_manager;

	std::unordered_map<size_t, std::unique_ptr<IAssetLoader>> loaders{};
	std::unordered_map<size_t, std::unordered_map<std::string, std::weak_ptr<void>>> assets{};
};

