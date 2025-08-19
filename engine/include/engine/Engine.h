#pragma once

#include "Scene/World.h"
#include "VisualInterface.h"
#include "AssetManager/AssetManager.h"
#include "engine/util/debug.h"

CREATE_ERROR_CATEGORY(engine, {
	{1, "Could not load project library"}
})

class ENGINE_API Engine {
public:
	static std::expected<Engine, Error> init() noexcept;
	static std::expected<Engine, Error> init(const std::string& path) noexcept;
	void tick() noexcept;
	void clean_up() noexcept;

	void run() noexcept;
	bool is_running() const noexcept;

	World world;
	VisualInterface visuals;
	AssetManager asset_manager;

private:
	Engine(World&& w, VisualInterface&& vi, AssetManager&& am)
		: world{std::move(w)}, visuals{std::move(vi)}, asset_manager{std::move(am)} {}

	static std::optional<Error> load_project_library(const std::string& path) noexcept;

	bool running{true};
};
