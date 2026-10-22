#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include "stb/stb_image.h"

ImageLoader::ImageLoader() {}

std::variant<ImageInfo, std::string> ImageLoader::load(const std::filesystem::path& path) {
    int width = 0;
    int height = 0;
    int actualChannels = 0;

    bool success = stbi_info(path.string().c_str(), &width, &height, &actualChannels) == 1;

    if (success) {
        ImageInfo imageInfo = ImageInfo();
        imageInfo.name = path.filename().string();
        imageInfo.width = width;
        imageInfo.height = height;
        return imageInfo;
    } else {
        return std::string(stbi_failure_reason());
    }
}

