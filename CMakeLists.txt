cmake_minimum_required(VERSION 3.5.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# # config for Docker
# set( nlohmann_json_DIR "/home/vcpkg/installed/x64-linux/share/nlohmann_json" )

# config for local machine
set( nlohmann_json_DIR "/mnt/d/logiciels_PA/vcpkg/installed/x64-linux/share/nlohmann_json" )

add_executable(main src/main.cpp src/ImageProcessor.cpp src/MosaicFromSmallCats.cpp src/ImageProcessorColor.cpp)

find_package( OpenCV REQUIRED )
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE ${OpenCV_LIBS} nlohmann_json::nlohmann_json pthread )

include(CTest)
include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${OpenCV_INCLUDE_DIRS} )

enable_testing()