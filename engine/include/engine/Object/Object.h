#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../util/debug.h"
#include "../Component/Component.h"
#include "engine/AssetManager/ObjectReflection/ReflectionMacro.h"
#include "engine/Object/RegistrationObject.h"

using ObjectID = size_t;

class ENGINE_API Object : public RegistrationObject {
public:
	static std::expected<Object, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	bool operator==(const Object& obj) const noexcept { return obj.id == id; }

	ObjectID get_id() const noexcept { return id; }

	void set_property_from_json(const Property& prop, const nlohmann::json& value) override;

	std::string name{};

	DEF_REGISTRAR(Object)
	
protected:
	Object(RegistrationObject&& reg_obj)
		: RegistrationObject{std::move(reg_obj)}, id{}, components{} {}

private:
	friend class Scene;

	ObjectID id;
	std::vector<Component*> components;
};

