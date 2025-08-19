#pragma once

#include <string>
#include "AssetLoader.h"
#include "engine/Scene/Scene.h"

class ENGINE_API SceneLoader : public AssetLoader<Scene> {
public:
	SceneLoader() { }

    std::expected<std::shared_ptr<Scene>, Error> load_typed(const std::string& file) override;
};

