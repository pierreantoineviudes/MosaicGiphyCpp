cmake_minimum_required(VERSION 3.5.0)
project(test_cmake VERSION 0.1.0 LANGUAGES C CXX)

add_executable(test_cmake src/main.cpp src/MyClass.cpp src/ImageProcessor.cpp src/MosaicFromSmallCats.cpp)

find_package( OpenCV REQUIRED )
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(test_cmake PRIVATE ${OpenCV_LIBS} nlohmann_json::nlohmann_json )

include(CTest)
include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${OpenCV_INCLUDE_DIRS} )

enable_testing()