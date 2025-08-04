#include <fstream>
#include "engine/AssetManager/TextLoader.h"

std::shared_ptr<std::string> TextLoader::load_typed(const std::string& file) {
	std::string ret{};
	std::ifstream{file} >> ret;
	return std::make_shared<std::string>(ret);
}
