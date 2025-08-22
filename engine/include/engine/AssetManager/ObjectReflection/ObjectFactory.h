#pragma once

#include <functional>
#include <memory>
#include "engine/util/debug.h"
#include "engine/Object/RegistrationObject.h"

template<typename TO, typename FROM>
std::unique_ptr<TO> static_unique_pointer_cast(std::unique_ptr<FROM>&& old){
	return std::unique_ptr<TO>{static_cast<TO*>(old.release())};
	// conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

CREATE_ERROR_CATEGORY(object_factory, {
	{1, "Unknown object type"}
})

class ENGINE_API ObjectFactory {
public:
	using CreateFn = std::function<std::expected<std::unique_ptr<RegistrationObject>, Error>()>;

	static ObjectFactory& instance() noexcept;

	void register_type(const std::string& name, CreateFn fn) noexcept;

	std::expected<std::unique_ptr<RegistrationObject>, Error> create(const std::string& name);

private:
	ObjectFactory() {}
	
	std::unordered_map<std::string, CreateFn> registry{};
};

//template<typename T>
//concept CanRegister = std::is_base_of<RegistrationObject, T>::value;

//template<CanRegister T>
template<typename T>
struct ObjectRegistrar {
	ObjectRegistrar(const char* name) {
		ObjectFactory::instance().register_type(name, [&]() -> std::expected<std::unique_ptr<RegistrationObject>, Error> {
			auto obj{T::init()};
			if (!obj.has_value()) return std::unexpected{obj.error()};
			return std::make_unique<T>(std::move(obj.value()));
		});
	}
};

