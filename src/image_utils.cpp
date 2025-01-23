#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../third_party/stb_image_resize2.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../third_party/stb_image_write.h" // Optional for saving resized images

void loadAndResizeImage(char *inputPath)
{
    // Load the input image
    int width, height, channels;
    unsigned char *inputImage = stbi_load("./data/image.jpg", &width, &height, &channels, 0);
}

int main()
{
    // Load the input image
    int width, height, channels;
    unsigned char *inputImage = stbi_load("./data/image.jpg", &width, &height, &channels, 0);
    if (!inputImage)
    {
        std::cerr << "Failed to load image.\n";
        return 1;
    }

    // Define new dimensions for resizing
    int newWidth = width / 2;
    int newHeight = height / 2;

    // Allocate memory for resized image
    unsigned char *resizedImage = new unsigned char[newWidth * newHeight * channels];

    try
    {
        // Resize the image
        stbir_resize(
            inputImage, width, height, 0,         // Input image and its dimensions
            resizedImage, newWidth, newHeight, 0, // Output image and its dimensions
            STBIR_RGB,                            // Pixel layout (e.g., RGB)
            STBIR_TYPE_UINT8,                     // Data type (e.g., 8-bit unsigned)
            STBIR_EDGE_CLAMP,                     // Edge behavior
            STBIR_FILTER_DEFAULT                  // Filter type
        );
        // Cleanup
        stbi_image_free(inputImage);
        delete[] resizedImage;

        std::cout << "Image resized and saved as resized.jpg\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Failed to resize image.\n";
        stbi_image_free(inputImage);
        delete[] resizedImage;
        return 1;
    }

    // Save the resized image
    if (!stbi_write_jpg("resized.jpg", newWidth, newHeight, channels, resizedImage, 100))
    {
        std::cerr << "Failed to save resized image.\n";
    }

    return 0;
}
