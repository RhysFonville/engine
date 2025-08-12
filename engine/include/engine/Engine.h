#pragma once

#include "Scene/World.h"
#include "VisualInterface.h"
#include "AssetManager/AssetManager.h"

class Engine {
public:
	static std::expected<Engine, Error> init() noexcept;
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

	bool running{true};
};

