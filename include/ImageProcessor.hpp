#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

using json = nlohmann::json;
using namespace std;

class ImageProcessor
{
public:
    ImageProcessor();
    json config;
    void processImageArr(int deb_inclu, int fin_exclue);
    void processImages();
    int taille_dalle;
    int max_num_threads;
    json dict_of_images;
};