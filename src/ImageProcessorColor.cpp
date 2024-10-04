#include "ImageProcessorColor.hpp"

ImageProcessorColor::ImageProcessorColor()
{
    std::ifstream configFile(std::string(PROJECT_ROOT) + "/constants.json");
    this->config = json::parse(configFile);
}