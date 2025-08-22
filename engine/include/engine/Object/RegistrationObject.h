#pragma once

#include <nlohmann/json.hpp>
#include "engine/util/debug.h"

struct Property {
	std::string type;
	std::string name;
	void* pointer;
};

class ENGINE_API RegistrationObject {
public:
	static std::expected<RegistrationObject, Error> init() noexcept;

	virtual const std::vector<Property> get_properties() const { return {}; }

	const std::string& get_registered_name() const noexcept { return name; }

	virtual void set_property_from_json(const Property& prop, const nlohmann::json& value) {}

protected:
	RegistrationObject() {}

private:
	std::string name;
	std::vector<Property> properties;
};

