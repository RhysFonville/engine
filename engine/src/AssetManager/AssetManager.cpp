#include "engine/AssetManager/AssetManager.h"
#include "engine/AssetManager/TextLoader.h"

std::expected<AssetManager, Error> AssetManager::init() noexcept {
	AssetManager ret{};
    ret.register_loader<std::string>(std::make_unique<TextLoader>());
	return ret;
}

