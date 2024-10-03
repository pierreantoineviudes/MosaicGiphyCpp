#include "ImageProcessor.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <thread>


using namespace std;
using namespace cv;
using json = nlohmann::json;

vector<cv::String> fn;
size_t countImages; // number of png files in images folder

ImageProcessor::ImageProcessor()
{
    // load config
    std::ifstream configFile(std::string(PROJECT_ROOT) + "/constants.json");
    this->config = json::parse(configFile);
    json dict_of_images;
    this->taille_dalle = config["TAILLE_DALLE"];
    this->max_num_threads = config["MAX_NUM_THREADS"];
    this->dict_of_images = dict_of_images;
}

void ImageProcessor::processImageArr(int deb_inclu, int fin_exclue)
{
    Mat img;
    for (size_t i = deb_inclu; i < fin_exclue; i++)
    {
        img = imread(fn[i]);
        if (!img.empty())
        {
            cvtColor(img, img, COLOR_RGB2GRAY);
            resize(img, img, Size(taille_dalle, taille_dalle));
            Scalar mean = cv::mean(img);

            // update jsonFile and save Img only if no mean value image already in
            if (dict_of_images[mean[0]].size() == 0)
            {
                cout << (float(i) - deb_inclu) / float(ceil(countImages * 1.0 / max_num_threads)) * 100 << "%" << endl;
                // save img
                String filePath = std::string(PROJECT_ROOT) + "/data_output/image_" + to_string(i) + ".jpg";
                imwrite(filePath, img);

                // update json file
                dict_of_images[mean[0]].push_back(filePath);
            }
        }
    }
}

void ImageProcessor::processImages()
{
    std::string dataDir = std::string(PROJECT_ROOT) + "data/*jpg";
    glob(dataDir, fn, true);
    countImages = fn.size();
    cout << "nb total d'images : " << countImages << endl;
    for (int i = 0; i < 255; i++)
    {
        vector<string> v;
        dict_of_images[i] = v;
    }

    // resize les images et les stocker dans data_output
    // multi threaded
    int size_tranche = ceil(countImages * 1.0 / max_num_threads);

    thread lds[max_num_threads];
    for (int k = 0; k < max_num_threads; k++)
    {
        int deb_inclu = k * size_tranche;
        int fin_exclue = (k + 1) * size_tranche;
        lds[k] = thread(&ImageProcessor::processImageArr, this, deb_inclu, fin_exclue);
    }

    // fin des threads
    for (int k = 0; k < max_num_threads; k++)
    {
        lds[k].join();
    }

    // save json object to file
    string s = dict_of_images.dump();
    ofstream out(config["TILES_DICT_PATH"]);
    out << s;
    out.close();
}