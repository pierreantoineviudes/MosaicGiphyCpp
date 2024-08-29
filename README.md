# Mosaic Image Generator with Cat Images

This project is a C++ application that generates a mosaic image from a given input image using a database of cat images. The mosaic is created by dividing the input image into smaller tiles, each of which is replaced with a cat image that closely matches the original tile's color.

## Features

- **Multithreaded Processing:** Utilizes multithreading to speed up the image processing and mosaic generation.
- **Image Processing with OpenCV:** Leverages the OpenCV library for efficient image processing and manipulation.
- **Cat Image Database:** Uses a database of cat images to create the mosaic effect.
- **Cross-Platform:** Can be compiled and run on various operating systems using CMake as the build system.

## Requirements

- **C++17 or later:** The project uses modern C++ features.
- **OpenCV:** The OpenCV library is required for image processing. You can install it via your package manager or build it from source.
- **CMake:** The project uses CMake as the build system. Make sure you have it installed on your machine.

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/pierreantoineviudes/MosaicGiphyCpp.git
   cd MosaicGiphyCpp
