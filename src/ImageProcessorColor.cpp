#include "ImageProcessorColor.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>

using namespace std;
using namespace cv;
using json = nlohmann::json;

vector<cv::String> fnColor;
size_t countImagesColor; // number of png files in images folder

ImageProcessorColor::ImageProcessorColor()
{
    // load config
    std::ifstream configFile(std::string(PROJECT_ROOT) + "/constants_color.json");
    this->config = json::parse(configFile);
    json dict_of_images;
    this->taille_dalle = config["TAILLE_DALLE"];
    this->max_num_threads = config["MAX_NUM_THREADS"];
    this->dict_of_images = dict_of_images;
}

void ImageProcessorColor::processImageArr(int deb_inclu, int fin_exclue)
{
    cout << "in processImages arr" << endl;
}

void ImageProcessorColor::processImages()
{
    cout << "in processImages" << endl;
    std::string dataDir = std::string(PROJECT_ROOT) + "data/*jpg";
    glob(dataDir, fnColor, true);
    countImagesColor = fnColor.size();
    cout << "nb total d'images : " << countImagesColor << endl;
    // n_color représnete la résoltuion de couleur qu'on va garder
    int n_color = 10;
    //initialisation du vecteur
    std::vector<std::vector<std::vector<std::string>>> vec3D(n_color, std::vector<std::vector<std::string>>(n_color, std::vector<std::string>(n_color, "")));
    
    // // initialisation du vecteur
    // for (int i = 0; i < n_color; i ++)
    // {
    //     for (int j = 0; j < n_color; j ++)
    //     {
    //         for (int k = 0; k < n_color; k++)
    //         {
    //             vec3D[i][j][k] = 
    //         }
    //     }
    // }

    // resize les images et les stocker dans data_output
    // multi threaded
    int size_tranche = ceil(countImagesColor * 1.0 / max_num_threads);

    thread lds[max_num_threads];
    for (int k = 0; k < max_num_threads; k++)
    {
        int deb_inclu = k * size_tranche;
        int fin_exclue = (k + 1) * size_tranche;
        lds[k] = thread(&ImageProcessorColor::processImageArr, this, deb_inclu, fin_exclue);
    }

    // fin des threads
    for (int k = 0; k < max_num_threads; k++)
    {
        lds[k].join();
    }


    // json object takes vec3D value
    dict_of_images = vec3D;
    // save json object to file
    string s = dict_of_images.dump();
    ofstream out(config["TILES_DICT_PATH"]);
    out << s;
    out.close();
}
