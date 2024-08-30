#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
using json = nlohmann::json;
using namespace std;
using namespace cv;

#define TAILLE_DALLE 50;
#define MAX_NUM_THREADS 8;

vector<cv::String> fn;
json dict_of_images;
size_t countImages; // number of png files in images folder
int taille_dalle = TAILLE_DALLE;
int max_num_threads = MAX_NUM_THREADS;

void processImagesArr(int deb_inclu, int fin_exclue)
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
                String filePath = "/home/paviudes/dev/mosaicgiphycpp/data_output/image_" + to_string(i) + ".jpg";
                imwrite(filePath, img);

                // update json file
                dict_of_images[mean[0]].push_back(filePath);
            }
        }
    }
}

void processImages()
{
    glob("/home/paviudes/dev/mosaicgiphycpp/data/*.jpg", fn, true);
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
        lds[k] = thread(processImagesArr, deb_inclu, fin_exclue);
    }

    // fin des threads
    for (int k = 0; k < max_num_threads; k++)
    {
        lds[k].join();
    }

    // save json object to file
    string s = dict_of_images.dump();
    ofstream out("/home/paviudes/dev/mosaicgiphycpp/output_small.json");
    out << s;
    out.close();
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    processImages();
    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;
    auto diff_sec = chrono::duration_cast<chrono::milliseconds>(diff);
    cout << "duration : " << diff_sec.count() << endl;
    return 0;
}