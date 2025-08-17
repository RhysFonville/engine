#include "engine/AssetManager/ObjectReflection/ObjectFactory.h"
#include "engine/Object/Object.h"

ObjectFactory& ObjectFactory::instance() noexcept {
	static ObjectFactory inst;
	return inst;
}

void ObjectFactory::register_type(const std::string& name, CreateFn fn) noexcept {
	registry[name] = std::move(fn);
}

std::expected<std::unique_ptr<Object>, Error> ObjectFactory::create(const std::string& name) {
	auto it = registry.find(name);
	if (it != registry.end()) {
		auto res{it->second()};
		if (!res.has_value()) return std::unexpected{res.error()};
		return std::move(*res);
	}
	return std::unexpected{Error{1, object_factory_category()}};
}
