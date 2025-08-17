#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../util/debug.h"
#include "../Component/Component.h"
#include "engine/AssetManager/ObjectReflection/ReflectionMacro.h"

using ObjectID = size_t;

struct Property {
	std::string type;
	std::string name;
	void* pointer;
};

class Object {
public:
	static std::expected<Object, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	ObjectID get_id() const noexcept { return id; }

	bool operator==(const Object& obj) const noexcept { return obj.id == id; }

	std::string name{};

	virtual const std::vector<Property> get_properties() const;

	void set_property_from_json(const Property& prop, const nlohmann::json& value);

	DEF_REGISTRAR(Object)
	
protected:
	Object() : id{}, components{} {}

private:
	friend class Scene;

	ObjectID id;
	std::vector<Component*> components;

	static std::vector<Property>& static_properties() {
		static std::vector<Property> properties;
		return properties;
	}
};

