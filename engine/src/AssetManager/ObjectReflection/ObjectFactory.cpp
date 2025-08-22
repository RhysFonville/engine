#include "engine/AssetManager/ObjectReflection/ObjectFactory.h"

ObjectFactory& ObjectFactory::instance() noexcept {
	static ObjectFactory factory;
	return factory;
}

void ObjectFactory::register_type(const std::string& name, CreateFn fn) noexcept {
	registry[name] = std::move(fn);
}

std::expected<std::unique_ptr<RegistrationObject>, Error> ObjectFactory::create(const std::string& name) {
	auto it = registry.find(name);
	if (it != registry.end()) {
		auto res{it->second()};
		if (!res.has_value()) return std::unexpected{res.error()};
		res.value()->name = name;
		return std::move(*res);
	}
	return std::unexpected{Error{1, object_factory_category()}};
}
