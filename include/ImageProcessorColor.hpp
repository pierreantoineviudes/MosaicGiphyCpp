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
    int taille_dalle;
    int max_num_threads;
    json dict_of_images;
    void processImageArr(int deb_inclu, int fin_exclue);
    void processImages();
};