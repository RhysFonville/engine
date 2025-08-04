#include "engine/AssetManager/AssetManager.h"
#include "engine/AssetManager/TextLoader.h"

AssetManager* AssetManager::asset_manager = nullptr;

AssetManager::AssetManager() {
    register_loader<std::string>(std::make_unique<TextLoader>());
}

AssetManager* AssetManager::get_instance() noexcept {
	if (asset_manager == nullptr) {
		asset_manager = new AssetManager{};
	}

	return asset_manager;
}

