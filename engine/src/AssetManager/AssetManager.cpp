#include "engine/AssetManager/AssetManager.h"

AssetManager* AssetManager::asset_manager = nullptr;

#define REGISTER_LOADER_TO_TYPE(LOADER, TYPE) \
	loaders[typeid(TYPE).hash_code()] = std::move(std::make_unique<LOADER>());

AssetManager::AssetManager() {
	REGISTER_LOADER_TO_TYPE(TextLoader, std::string)
}

AssetManager* AssetManager::get_instance() noexcept {
	if(asset_manager == nullptr) {
		asset_manager = new AssetManager{};
	}

	return asset_manager;
}
