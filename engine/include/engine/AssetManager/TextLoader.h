#pragma once

#include <string>
#include "AssetLoader.h"

class TextLoader : public AssetLoader<std::string> {
public:
	TextLoader() { }

    std::expected<std::shared_ptr<std::string>, Error> load_typed(const std::string& file) override;
};

