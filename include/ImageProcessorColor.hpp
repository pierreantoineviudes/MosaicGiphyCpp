#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

using json = nlohmann::json;
using namespace std;

class ImageProcessorColor
{
    public:
    ImageProcessorColor();
    json config;
};