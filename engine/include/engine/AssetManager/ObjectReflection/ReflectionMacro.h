#pragma once

#include <ranges>
#include <algorithm>

#define DEF_REGISTRAR(class_name) static ObjectRegistrar<class_name> registrar;

#define BEGIN_CLASS(class_name) \
private: \
	using ClassType = class_name; \
	static std::vector<Property>& static_properties() { \
		static std::vector<Property> properties; \
		return properties; \
	} \
public: \
	const std::vector<Property>& get_properties() const override { \
		std::vector<Property> parent_properties{Object::get_properties()}; \
		std::vector<Property> properties{static_properties()}; \
		properties.reserve(pp.size()); \
		properties.insert(properties.end(), parent_properties); \
		return properties; \
	} \
	DEF_REGISTRAR(class_name)

#define END_CLASS(class_name) \
ObjectRegistrar<class_name> class_name::registrar{#class_name};

#define PROPERTY(type, name, pointer) \
	type name{}; \
	struct AutoRegister_##name { \
		AutoRegister_##name(type) { \
			ClassType::static_properties().push_back({#name, #type, pointer}); \
		} \
	} auto_register_##name{&name};
