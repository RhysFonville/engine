#include <engine/Engine.h>

int main() {
	Engine engine{};
	if (auto res{engine.init()}) {
		log(LogLevel::FATAL, res.value());
		return res.value();
	}

	auto scene1{std::make_shared<Scene>()};
	scene1->add_object(Object{});

	auto scene2{std::make_shared<Scene>()};
	scene2->add_object(Object{});
	scene2->add_object(Object{});

	if (scene1->get_objects().size() >= scene2->get_objects().size()) {
		log(LogLevel::FATAL, "Scene 1 with only 1 object ended up having more objects with only 2 objects added.");
		return EXIT_FAILURE;
	}

	engine.world.add_scene(scene1);
	if (engine.world.get_active_scene()->get_objects() != scene1->get_objects()) {
		log(LogLevel::FATAL, "Active scene not equal to added scene with activate flag enabled.");
		return EXIT_FAILURE;
	}

	engine.world.add_scene(scene2, false);
	if (engine.world.get_active_scene()->get_objects() != scene1->get_objects()) {
		log(LogLevel::FATAL, "Active scene did not stay the same after new scene was added with activate flag enabled.");
		return EXIT_FAILURE;
	}

	if (auto res{engine.world.activate_scene(0)}) {
		log(LogLevel::FATAL, res.value());
		return EXIT_FAILURE;
	}

	if (engine.world.get_active_scene()->get_objects() != scene1->get_objects()) {
		log(LogLevel::FATAL, "Switch to first active scene did not work.");
		return EXIT_FAILURE;
	}

	if (auto res{engine.world.activate_scene(0)}) {
		log(LogLevel::FATAL, res.value());
		return EXIT_FAILURE;
	}

	if (engine.world.get_active_scene()->get_objects() != scene1->get_objects()) {
		log(LogLevel::FATAL, "Switch to same scene did not work.");
		return EXIT_FAILURE;
	}

	if (auto res{engine.world.activate_scene(3498)}) {
		log(LogLevel::FATAL, res.value());
	} else {
		return EXIT_FAILURE;
	}

	if (auto res{engine.world.add_scene(nullptr)}) {
		log(LogLevel::FATAL, res.value());
	} else {
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}

