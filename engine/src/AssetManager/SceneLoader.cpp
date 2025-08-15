#include "engine/AssetManager/SceneLoader.h"
#include "engine/AssetManager/ObjectReflection/ObjectFactory.h"
#include "engine/Scene/Scene.h"

std::expected<std::shared_ptr<Scene>, Error> SceneLoader::load_typed(const std::string& file) {
	std::shared_ptr<Scene> scene{};
	{
		auto temp_scene{Scene::init()};
		if (!temp_scene.has_value()) return std::unexpected{temp_scene.error()};
		scene = std::make_shared<Scene>(std::move(*temp_scene));
	}

	nlohmann::json json{};
	try {
		json = nlohmann::json::parse(file);
	} catch (const std::exception& e) {
		return std::unexpected{Error{4, asset_loader_category()}};
	}

	for (auto& obj_data : json["objects"]) {
		std::string type{obj_data["type"]};

		auto obj{ObjectFactory::instance().create(type)};
		if (!obj) {
			std::cerr << "Unknown object type: " << type << "\n";
			continue;
		}

		scene->add_object(std::move(obj));
	}

	return std::move(scene);
}
