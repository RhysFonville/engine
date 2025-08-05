#include <fstream>
#include <sstream>
#include "engine/AssetManager/TextLoader.h"

std::expected<std::shared_ptr<std::string>, Error> TextLoader::load_typed(const std::string& file) {
	std::ifstream in{file};
	if (!in.is_open()) return std::unexpected{Error{1, asset_loader_category()}};

	std::stringstream ret{};
	ret << in.rdbuf();

	in.close();
	if (in.is_open()) return std::unexpected{Error{2, asset_loader_category()}};

	return std::make_shared<std::string>(ret.str());
}
