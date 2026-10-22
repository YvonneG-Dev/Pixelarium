#pragma once

#include <variant>
#include <filesystem>
#include <string>
#include "../model/ImageInfo.h"

class ImageLoader
{
public:
    ImageLoader();

    std::variant<ImageInfo, std::string> load(const std::filesystem::path& path);
};


