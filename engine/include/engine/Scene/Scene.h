#pragma once

#include <unordered_map>
#include <typeindex>
#include <concepts>
#include <ranges>
#include <optional>
#include "../Object/Object.h"

class Scene;

template<typename T> requires std::derived_from<T, Component>
class ENGINE_API ComponentStorage {
public:
	T* add(ObjectID e, const std::unique_ptr<T>& component) noexcept {
		if (object_to_index.find(e) != object_to_index.end()) {
			return data[object_to_index[e]] = std::move(component);
		}
		object_to_index[e] = data.size();
		objects.push_back(e);
		data.push_back(std::move(component));
		return data.back().get();
	}

	void remove(ObjectID e) noexcept {
		auto it{object_to_index.find(e)};
		if (it == object_to_index.end()) return;
		size_t index{it->second};
		size_t lastIndex{data.size()-1};
		data[index] = data[lastIndex];
		objects[index] = objects[lastIndex];
		object_to_index[objects[index]] = index;
		data.pop_back();
		objects.pop_back();
		object_to_index.erase(it);
	}

	bool has(ObjectID e) const noexcept {
		return object_to_index.find(e) != object_to_index.end();
	}

	std::optional<T*> get(ObjectID e) const noexcept {
		if (!has(e)) return std::nullopt;
		return data[object_to_index.at(e)].get();
	}

	const std::vector<ObjectID>& get_objects() const noexcept { return objects; }
	const std::vector<std::unique_ptr<T>>& get_data() const noexcept { return data; }

private:
	std::vector<std::unique_ptr<T>> data;
	std::vector<ObjectID> objects;
	std::unordered_map<ObjectID, size_t> object_to_index;
};

// -------- Scene --------
class ENGINE_API Scene {
public:
	static std::expected<Scene, Error> init() noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	template<typename T> requires std::derived_from<T, Object>
	Object* add_object(std::unique_ptr<T>&& object) noexcept {
		object->id = object_id_counter++;
		return (objects[object->id] = std::move(object)).get();
	}

	template<typename T> requires std::derived_from<T, Object>
	std::expected<Object*, Error> add_object() noexcept {
		std::expected<T, Error> obj{T::init()};
		if (!obj.has_value()) return std::unexpected{obj.error()};

		obj.value().id = object_id_counter++;
		return (objects[obj.value().id] = std::make_unique<T>(obj.value())).get();
	}

	template<typename T>
	T* add_component(ObjectID object, std::unique_ptr<T>&& component) noexcept {
		objects[object]->components.emplace_back(component.get());
		auto& storage{get_storage<T>()};
		return storage.add(object, std::move(component));
	}
	template<typename T>
	T* add_component(Object* object, std::unique_ptr<T>&& component) noexcept {
		return add_component(object->get_id(), std::move(component));
	}

	template<typename T>
	void remove_component(ObjectID object) {
		auto type_id{get_component<T>()};
		auto it{component_stores.find(type_id)};
		if (it != component_stores.end()) {
			auto* pool{static_cast<ComponentStorage<T>*>(it->second.get())};
			objects[object]->components.erase(std::ranges::find(objects[object]->components, pool->get(object)));
			pool->remove(object);
		}
	}

	template<typename T> requires std::derived_from<T, Component>
	bool has_component(ObjectID e) const noexcept {
		return get_storage<T>().has(e);
	}

	template<typename T> requires std::derived_from<T, Component>
	std::optional<T*> get_component(ObjectID e) noexcept {
		return get_storage<T>().get(e);
	}

	std::vector<Object*> get_objects() const noexcept;

	template<typename T, typename Func> requires std::derived_from<T, Component>
	void for_each(Func func) noexcept {
		auto& storage{get_storage<T>()};
		auto& comps{storage.getData()};
		auto& ents{storage.get_objects()};
		for (size_t i = 0; i < comps.size(); i++) {
			func(ents[i], comps[i]);
		}
	}

private:
	Scene() : component_stores{}, objects{} {}

	template<typename T> requires std::derived_from<T, Component>
	ComponentStorage<T>& get_storage() const noexcept {
		std::type_index ti(typeid(T));
		if (component_stores.find(ti) == component_stores.end()) {
			component_stores[ti] = std::make_shared<ComponentStorage<T>>();
		}
		return *std::static_pointer_cast<ComponentStorage<T>>(component_stores[ti]);
	}

	mutable std::unordered_map<std::type_index, std::shared_ptr<void>> component_stores;
	std::unordered_map<ObjectID, std::unique_ptr<Object>> objects;

	inline static ObjectID object_id_counter{0};
};
