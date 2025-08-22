#pragma once

#include <ranges>
#include <algorithm>
#include "ObjectFactory.h"

#define DEF_REGISTRAR(class_name) static ObjectRegistrar<class_name> registrar;

#define BEGIN_CLASS(class_name) \
private: \
	using ClassType = class_name; \
public: \
	DEF_REGISTRAR(class_name)

#define BEGIN_DEFS(class_name) \
ObjectRegistrar<class_name> ATTR_USED class_name::registrar{#class_name};

#define PROPERTY(type, name) \
type name{}; \
struct PROJECT_API AutoRegister_##name { \
	AutoRegister_##name(std::vector<Property>* prop_pointer, void* pointer) { \
		prop_pointer->push_back({#type, #name, pointer}); \
	} \
} auto_register_##name{&properties, &name};

