#pragma once

#include <functional>
#include <memory>
#include <concepts>
#include "engine/util/debug.h"
#include "engine/Object/RegistrationObject.h"

CREATE_ERROR_CATEGORY(object_factory, {
	{1, "Unknown object type"}
})

class Object;

class ENGINE_API ObjectFactory {
public:
	using CreateFn = std::function<std::expected<std::unique_ptr<RegistrationObject>, Error>()>;

	static ObjectFactory& instance() noexcept;

	void register_type(const std::string& name, CreateFn fn) noexcept;

	std::expected<std::unique_ptr<Object>, Error> create(const std::string& name);

private:
	ObjectFactory() {}
	
	std::unordered_map<std::string, CreateFn> registry{};
};

template<typename T> requires std::derived_from<T, RegistrationObject>
struct ENGINE_API ObjectRegistrar {
	ObjectRegistrar(const char* name) {
		ObjectFactory::instance().register_type(name, []() -> std::expected<std::unique_ptr<RegistrationObject>, Error> {
			auto obj{T::init()};
			if (!obj.has_value()) return std::unexpected{obj.error()};
			return std::make_unique<T>(std::move(obj.value()));
		});
	}
};

