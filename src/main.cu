#include <iostream>
#include "directoryUtils.h"
#include "imageProcessor.h"
#include <filesystem>

int main()
{
    const std::string inputDirectory = "./data";  // Path to input directory
    const std::string outputDirectory = "./output_data2"; // Path to output directory
    const int newWidth = 256;
    const int newHeight = 256;

    // Create the output directory if it doesn't exist
    std::filesystem::create_directories(outputDirectory);

    // Get all .jpg file paths from the input directory
    std::vector<std::string> imagePaths = get_image_paths(inputDirectory);
    if (imagePaths.empty())
    {
        std::cerr << "No .jpg files found in the directory: " << inputDirectory << std::endl;
        return 1;
    }

    // Process each image
    for (const std::string &imagePath : imagePaths)
    {
        std::string outputPath = outputDirectory + "/" + std::filesystem::path(imagePath).filename().string();
        process_image(imagePath, outputPath, newWidth, newHeight);
    }

    return 0;
}
