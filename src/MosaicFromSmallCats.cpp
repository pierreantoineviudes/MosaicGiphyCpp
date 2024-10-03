#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include "MosaicFromSmallCats.hpp"

using json = nlohmann::json;
using namespace std;
using namespace cv;
using namespace chrono;

MosaicFromSmallCats::MosaicFromSmallCats()
{
    // load config file
    std::ifstream configFile(std::string(PROJECT_ROOT) + "/constants.json");
    this->config = json::parse(configFile);
    this->max_num_threads = config["MAX_NUM_THREADS"];
    this->taille_dalle = config["TAILLE_DALLE"];
    this->bigImg = imread(config["PATH_BIG_IMAGE"]);
    this->width = bigImg.size().height;
    this->height = bigImg.size().width;
    this->newWidth = config["NEW_WIDTH"];
    this->newHeight = height * float(newWidth) / float(width);
    this->outputArr = Mat::zeros(newWidth * taille_dalle, newHeight * taille_dalle, CV_8UC1);
    std::ifstream f(config["TILES_DICT_PATH"]);
    this->json_data = json::parse(f);
}

void MosaicFromSmallCats::createMosaicUneTranche(int deb_inclu, int fin_exclue)
{
    for (int i = deb_inclu; i < fin_exclue; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            int value = (int)(bigImg.at<uchar>(j, i));
            // Check if value exists in dictionary
            while (json_data[value].size() == 0)
            {
                if (value > 128)
                {
                    value += -1;
                }
                else
                {
                    value += 1;
                }
            }
            if (json_data[value].size() > 0)
            {
                // Load the first image corresponding to the value
                string fileName = json_data[value][0];
                Mat smallImage = imread(fileName, IMREAD_GRAYSCALE);

                if (!smallImage.empty())
                {
                    // Replace the corresponding pixels in the output array
                    for (int k = 0; k < taille_dalle; k++)
                    {
                        for (int l = 0; l < taille_dalle; l++)
                        {
                            uchar &value = smallImage.at<uchar>(l, k);
                            uchar &newValue = outputArr.at<uchar>(
                                j * taille_dalle + l,
                                i * taille_dalle + k);
                            newValue = value;
                        }
                    }
                }
                else
                {
                    cerr << "Failed to read small image: " << fileName << endl;
                }
            }
            else
            {
                // cout << "error json" << endl;
            }
        }
    }
}

void MosaicFromSmallCats::createMosaic()
{
    // resze t new height and width
    resize(bigImg, bigImg, Size(newHeight, newWidth));
    cvtColor(bigImg, bigImg, COLOR_RGB2GRAY);

    // multi threaded create mosaic
    int size_tranche = ceil(newHeight * 1.0 / max_num_threads);

    thread lds[max_num_threads];

    for (int k = 0; k < max_num_threads; k++)
    {
        int deb_inclu = k * size_tranche;
        int fin_exclue = (k + 1) * size_tranche;
        lds[k] = thread(&MosaicFromSmallCats::createMosaicUneTranche, this, deb_inclu, fin_exclue);
    }

    // fin des threads
    for (int k = 0; k < max_num_threads; k++)
    {
        lds[k].join();
    }

    // save big image
    imwrite(std::string(PROJECT_ROOT) + "/outputsmall.jpg", outputArr);
    cout << "succeded to save image !! " << endl;
}