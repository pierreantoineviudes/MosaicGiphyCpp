#include "directoryUtils.h"
#include <filesystem>

std::vector<std::string> get_image_paths(const std::string& directoryPath) {
    std::vector<std::string> imagePaths;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            imagePaths.push_back(entry.path().string());
        }
    }
    return imagePaths;
}
