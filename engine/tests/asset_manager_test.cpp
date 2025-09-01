#include <cstdlib>
#include <engine/Engine.h>
#include <fstream>

int main() {
    std::ofstream f{"test_files/test.txt"};
    if (!f.is_open()) {
        log(LogLevel::Fatal, "Unable to open file");
        return EXIT_FAILURE;
    }

    std::string file_text{"Hello this is my file\nThis is a seccond line"};
    f << file_text;

    f.close();
    if (f.is_open()) {
        log(LogLevel::Fatal, "Unable to close file");
        return EXIT_FAILURE;
    }

	auto engine{Engine::init()};
	if (!engine.has_value()) {
		log(LogLevel::Fatal, engine.error());
		return EXIT_FAILURE;
	}
	AssetManager& am{engine.value().asset_manager};

    auto str{am.load<std::string>("test_files/test.txt")};
    if (!str.has_value()) {
        log(str.error());
        return EXIT_FAILURE;
    }
	auto str2{am.load<std::string>("test_files/test.txt")};
    if (!str2.has_value()) {
        log(str2.error());
        return EXIT_FAILURE;
    }
    if (str.value() != str2.value()) {
        log(LogLevel::Error, "Pointers are not equal");
        return EXIT_FAILURE;
    }
    if (*str.value() != file_text) {
        log(LogLevel::Error, "Text loader output not correct");
        return EXIT_FAILURE;
    }

    if (am.load<std::string>("file_that_doesnt_exist.txt").has_value()) {
        log(LogLevel::Error, "Loaded result is returned when passed a file that does not exist");
    }
    if (am.load<std::string>("~/").has_value()) {
        log(LogLevel::Error, "Loaded result is returned when passed a directory");
    }

	return EXIT_SUCCESS;
}

