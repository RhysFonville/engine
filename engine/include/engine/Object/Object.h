#pragma once

#include <string>
#include <vector>
#include "../util/debug.h"
#include "../Component/Component.h"

using ObjectID = size_t;

class Object {
public:
	static std::expected<Object, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	ObjectID get_id() const noexcept { return id; }

	bool operator==(const Object& obj) const noexcept { return obj.id == id; }

	std::string name{};

private:
	friend class Scene;

	Object() : id{}, components{} {}

	ObjectID id;
	std::vector<Component*> components;
};

