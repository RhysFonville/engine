#include <fstream>
#include "engine/AssetManager/SceneLoader.h"
#include "engine/AssetManager/ObjectReflection/ObjectFactory.h"
#include "engine/Scene/Scene.h"

std::expected<std::shared_ptr<Scene>, Error> SceneLoader::load_typed(const std::string& file) {
	if (std::filesystem::path{file}.extension() != ".json") return std::unexpected{Error{4, asset_loader_category()}};
	
	std::shared_ptr<Scene> scene{};
	{
		auto temp_scene{Scene::init()};
		if (!temp_scene.has_value()) return std::unexpected{temp_scene.error()};
		scene = std::make_shared<Scene>(std::move(*temp_scene));
	}

	std::ifstream in{file};
	if (!in.is_open()) return std::unexpected{Error{1, asset_loader_category()}};

	nlohmann::json json{};
	try {
		json = nlohmann::json::parse(in);
	} catch (const nlohmann::json::parse_error& e) {
		in.close();
		std::string what = e.what();
		return std::unexpected{Error{5, asset_loader_category()}};
	}

	in.close();
	if (in.is_open()) return std::unexpected{Error{2, asset_loader_category()}};

	for (auto& obj_data : json["objects"]) {
		std::string type{obj_data["type"]};

		auto obj{ObjectFactory::instance().create(type)};
		if (!obj.has_value()) {
			return std::unexpected{obj.error()};
			continue;
		}

		// Set properties from JSON
		for (const auto& prop : obj.value()->get_properties()) {
			if (obj_data.contains(prop.name)) {
				obj.value()->set_property_from_json(prop, obj_data[prop.name]);
			}
		}

		scene->add_object(std::move(obj.value()));
	}

	return std::move(scene);
}
