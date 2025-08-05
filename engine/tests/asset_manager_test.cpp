#include "engine/util/defines.h"
#include <cstdlib>
#include <engine/AssetManager/AssetManager.h>
#include <iostream>
#include <fstream>

int main() {
    std::ofstream f{"test.txt"};
    if (!f.is_open()) {
        log(LogLevel::FATAL, "Unable to open file");
        return EXIT_FAILURE;
    }

    std::string file_text{"Hello this is my file\nThis is a seccond line"};
    f << file_text;

    f.close();
    if (f.is_open()) {
        log(LogLevel::FATAL, "Unable to close file");
        return EXIT_FAILURE;
    }

	AssetManager* am{AssetManager::get_instance()};
    if (am == nullptr) return EXIT_FAILURE;

    auto str{am->load<std::string>("test.txt")};
    if (!str.has_value()) {
        log(str.error());
        return EXIT_FAILURE;
    }
	auto str2{am->load<std::string>("test.txt")};
    if (!str2.has_value()) {
        log(str2.error());
        return EXIT_FAILURE;
    }
    if (str.value() != str2.value()) {
        log(LogLevel::ERROR, "Pointers are not equal");
        return EXIT_FAILURE;
    }
    if (*str.value() != file_text) {
        log(LogLevel::ERROR, "Text loader output not correct");
        return EXIT_FAILURE;
    }

    if (am->load<std::string>("file_that_doesnt_exist.txt").has_value()) {
        log(LogLevel::ERROR, "Loaded result is returned when passed a file that does not exist");
    }
    if (am->load<std::string>("~/").has_value()) {
        log(LogLevel::ERROR, "Loaded result is returned when passed a directory");
    }

	return EXIT_SUCCESS;
}

