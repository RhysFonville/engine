#pragma once

#include <functional>
#include <memory>
#include "engine/util/debug.h"

CREATE_ERROR_CATEGORY(object_factory, {
	{1, "Unknown object type"}
})

class Object;

class ObjectFactory {
public:
	using CreateFn = std::function<std::expected<std::unique_ptr<Object>, Error>()>;

	void register_type(const std::string& name, CreateFn fn) noexcept;

	std::expected<std::unique_ptr<Object>, Error> create(const std::string& name);

private:
	std::unordered_map<std::string, CreateFn> registry{};
};

inline ObjectFactory& get_object_factory_instance() noexcept {
	static ObjectFactory inst;
	return inst;
}

template<typename T>
struct ObjectRegistrar {
	ObjectRegistrar(const char* name) {
		get_object_factory_instance().register_type(name, []() -> std::expected<std::unique_ptr<Object>, Error> {
			auto obj{T::init()};
			if (!obj.has_value()) return std::unexpected{obj.error()};
			return std::make_unique<T>(std::move(obj.value()));
		});
	}
};

