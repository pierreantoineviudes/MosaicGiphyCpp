# MOSAICCATS

## Project Description

MosaicCats is a C++ application that generates a mosaic image using a collection of smaller images, inspired by the Giphy format. It leverages powerful libraries such as OpenCV for image processing and nlohmann_json for handling JSON data. JSON is used for configuration and storing data about images.

## Features

- Create mosaic images from a set of small images.
- Use of OpenCV for advanced image processing.
- Supports JSON configuration for input parameters.

## Prerequisites

Before you begin, ensure you have the following installed:

- [Docker](https://www.docker.com/get-started) (for containerization)

If you prefer to use it locally (not recommended). You will need to install [OpenCV](https://opencv.org/), C++ buid tools, [CMake](https://cmake.org/), [vcpkg](https://vcpkg.io/en/), and install [nlohmann-json](https://github.com/nlohmann/json) with vcpkg.

## Installation

### Using Docker

There are two ways of using the dockerized image of the project.

- Either, you build the docker images from sources and then you can modify the `input.jpg` or `constants.json` from source files.
- Or, you can run the image published on ***DockerHub*** in interactive mode. You will be able to send your own config file `constants.json` and `input.jpg` with a simple `docker cp` command.

#### Building the docker image from sources

```bash
git clone https://github.com/pierreantoineviudes/MosaicGiphyCpp.git
cd MosaicGiphyCpp
```

Then, replace `input.jpg` with the image you want to do the mosaic from.
You can set the settings in the `constants.json` file i.e. change the number of threads used for the execution, the tile size and final image width (image proportions are kept).

You are finally set to build the image !!!

```bash
docker build -t mosaicimage .
docker run -name mosaiccontainer mosaicimage
```

Then you will have to get the output image out of the container to be able to access it from your local machine:

```bash
docker cp mosaiccontainer:/app/outputsmall.jpg ./myoutputpath.jpg
```

#### Using the image from DockerHub

```bash
docker run --name mymosaicapp -it yourusername/mosaicimage:latest /bin/bash
```

Then replace your own config files and input (from another terminal)

```bash
docker cp ./pathtoyourowninput.jpg mymosaicapp:/app/input.jpg
docker cp ./pathtoyourownconfig.json mymosaicapp:/app/constants.json
```

And then, run the app from the interactive shell in the container (executable of the app is in the `/app/build` folder)

```bash
./build/main
```
