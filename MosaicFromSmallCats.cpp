#define MAX_NUM_THREADS 8
#define TAILLE_DALLE 50
#define ALPHA 5;

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
using json = nlohmann::json;
using namespace std;
using namespace cv;
using namespace chrono;

// DEFINE GLOBAL VARS

// open the big image
Mat bigImg = imread("/home/paviudes/dev/mosaicgiphycpp/images/jeanne.jpg");
int width = bigImg.size().height;
int height = bigImg.size().width;
int newWidth = width / ALPHA;
int newHeight = height / ALPHA;
Mat output_arr = Mat::zeros( newWidth *TAILLE_DALLE, newHeight * TAILLE_DALLE, CV_8UC1);
// open dict of images path
std::ifstream f("/home/paviudes/dev/mosaicgiphycpp/output_small.json");
json json_data = json::parse(f);

void createMosaicUneTranche(int deb_inclu, int fin_exclue)
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
                } else
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
                    for (int k = 0; k < TAILLE_DALLE; k++)
                    {
                        for (int l = 0; l < TAILLE_DALLE; l++)
                        {
                            uchar &value = smallImage.at<uchar>(l, k);
                            uchar &newValue = output_arr.at<uchar>(
                                j * TAILLE_DALLE + l,
                                i * TAILLE_DALLE + k
                                );
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

void createMosaic()
{
    // resze t new height and width
    resize(bigImg, bigImg, Size(newHeight, newWidth));
    cvtColor(bigImg, bigImg, COLOR_RGB2GRAY);

    // multi threaded create mosaic
    int size_tranche = ceil(newHeight * 1.0 / MAX_NUM_THREADS);

    thread lds[MAX_NUM_THREADS];

    for (int k = 0; k < MAX_NUM_THREADS; k++)
    {
        int deb_inclu = k * size_tranche;
        int fin_exclue = (k + 1) * size_tranche;
        lds[k] = thread(createMosaicUneTranche, deb_inclu, fin_exclue);
    }

    // fin des threads
    for (int k = 0; k < MAX_NUM_THREADS; k++)
    {
        lds[k].join();
    }

    // save big image
    imwrite("/home/paviudes/dev/mosaicgiphycpp/outputsmall.jpg", output_arr);
    cout << "succeded to save image !! " << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    createMosaic();
    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;
    auto diff_sec = chrono::duration_cast<chrono::milliseconds>(diff);
    cout << "duration : " << diff_sec.count() << endl;
    return 0;
}