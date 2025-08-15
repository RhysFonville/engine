#pragma once

#include <functional>
#include <memory>
#include "engine/util/debug.h"

class Object;

CREATE_ERROR_CATEGORY(object_factory, {
	{1, "Unknown object type"}
})

class ObjectFactory {
public:
	using CreateFn = std::function<std::expected<std::unique_ptr<Object>, Error>()>;

	static ObjectFactory& instance() {
		static ObjectFactory inst;
		return inst;
	}

	void register_type(const std::string& name, CreateFn fn) {
		registry[name] = std::move(fn);
	}

	std::expected<std::unique_ptr<Object>, Error> create(const std::string& name) {
		auto it = registry.find(name);
		if (it != registry.end()) {
			return it->second();
		}
		return std::unexpected{Error{1, object_factory_category()}};
	}

private:
	std::unordered_map<std::string, CreateFn> registry;
};

template<typename T>
struct ObjectRegistrar {
	ObjectRegistrar(const char* name) {
		ObjectFactory::instance().register_type(name, []() -> std::expected<std::unique_ptr<Object>, Error> {
			auto obj{T::init()};
			if (!obj.has_value()) return std::unexpected{obj.error()};
			return std::make_unique<T>(std::move(obj.value()));
		});
	}
};
