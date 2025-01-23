#include "imageProcessor.h"
#include <iostream>
#include <cuda_runtime.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb_image.h"
#include "../third_party/stb_image_write.h"

// CUDA kernels
__global__ void rgb_to_grayscale(const unsigned char *input, unsigned char *grayscale, int width, int height, int channels)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int totalPixels = width * height;

    if (idx < totalPixels)
    {
        int r = input[idx * channels + 0];
        int g = input[idx * channels + 1];
        int b = input[idx * channels + 2];
        grayscale[idx] = static_cast<unsigned char>(0.2126f * r + 0.7152f * g + 0.0722f * b);
    }
}

void process_image(const std::string &inputPath, const std::string &outputPath, int width, int height)
{
    int channels;
    unsigned char *h_inputImage = stbi_load(inputPath.c_str(), &width, &height, &channels, 0);
    if (!h_inputImage)
    {
        std::cerr << "Failed to load image: " << inputPath << std::endl;
        return;
    }

    if (channels < 3)
    {
        std::cerr << "Input image must have at least 3 channels (RGB)." << std::endl;
        stbi_image_free(h_inputImage);
        return;
    }

    unsigned char *h_grayscaleImage = new unsigned char[width * height];
    unsigned char *d_inputImage, *d_grayscaleImage;
    unsigned char *h_outputImage;
    cudaMalloc(&d_inputImage, width * height * channels * sizeof(unsigned char));
    cudaMalloc(&d_grayscaleImage, width * height * sizeof(unsigned char));

    cudaMemcpy(d_inputImage, h_inputImage, width * height * channels * sizeof(unsigned char), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (width * height + threadsPerBlock - 1) / threadsPerBlock;

    // perform RGB to grayscale
    rgb_to_grayscale<<<blocksPerGrid, threadsPerBlock>>>(d_inputImage, d_grayscaleImage, width, height, channels);
    cudaDeviceSynchronize();

    cudaMemcpy(h_outputImage, d_grayscaleImage, width * height * sizeof(unsigned char), cudaMemcpyDeviceToHost);

    if (!stbi_write_jpg(outputPath.c_str(), width, height, 1, h_outputImage, 100))
    {
        std::cerr << "Failed to save resized grayscale image: " << outputPath << std::endl;
    }
    else
    {
        std::cout << "Processed and saved: " << outputPath << std::endl;
    }

    stbi_image_free(h_inputImage);
    delete[] h_grayscaleImage;
    delete[] h_outputImage;
    cudaFree(d_inputImage);
    cudaFree(d_grayscaleImage);
}