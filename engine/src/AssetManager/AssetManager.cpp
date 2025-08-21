#include "engine/AssetManager/AssetManager.h"
#include "engine/AssetManager/TextLoader.h"
#include "engine/AssetManager/SceneLoader.h"

std::expected<AssetManager, Error> AssetManager::init() noexcept {
	AssetManager ret{};
	ret.register_loader<std::string>(std::make_unique<TextLoader>());
	ret.register_loader<Scene>(std::make_unique<SceneLoader>());
	return std::move(ret);
}

