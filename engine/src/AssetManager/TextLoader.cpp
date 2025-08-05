#include <fstream>
#include "engine/AssetManager/TextLoader.h"
#include "engine/AssetManager/AssetLoader.h"

std::expected<std::shared_ptr<std::string>, Error> TextLoader::load_typed(const std::string& file) {
	std::string ret{};
	std::ifstream in{file};
    if (!in.is_open()) return std::unexpected{Error{1, asset_loader_category()}};

    in >> ret;
    log(LogLevel::INFO, ret);
    log("text");

    in.close();
    if (in.is_open()) return std::unexpected{Error{2, asset_loader_category()}};

	return std::make_shared<std::string>(ret);
}
