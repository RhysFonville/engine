#pragma once

#include <string>
#include "AssetLoader.h"

class TextLoader : public AssetLoader<std::string> {
public:
	TextLoader() { }

	std::shared_ptr<std::string> load_typed(const std::string& file);
};

