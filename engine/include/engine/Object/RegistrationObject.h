#pragma once

#include <nlohmann/json.hpp>
#include "engine/util/debug.h"

struct ENGINE_API IProperty {
	IProperty(const std::string& name) : name{name} {}
	virtual ~IProperty() = default;
	std::string name;
};

template <typename T>
struct ENGINE_API Property : public IProperty {
	Property(const std::string& name, T* pointer) : IProperty{name}, pointer{pointer} {}
	T* pointer;
};

class ENGINE_API RegistrationObject {
public:
	static std::expected<RegistrationObject, Error> init() noexcept;

	RegistrationObject(RegistrationObject&&) noexcept;
	RegistrationObject& operator=(RegistrationObject&&) noexcept;
	~RegistrationObject();

	const std::vector<IProperty*> get_properties() const {
		return properties
			| std::views::transform([](const auto& p) { return p.get(); })
			| std::ranges::to<std::vector>();
	}

	const std::string& get_registered_name() const noexcept { return name; }

protected:
	RegistrationObject() noexcept;

	std::vector<std::unique_ptr<IProperty>> properties;

private:
	friend class ObjectFactory;
	std::string name;
};

