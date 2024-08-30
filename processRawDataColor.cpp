#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
using json = nlohmann::json;
using namespace std;
using namespace cv;

void processImages()
{

    int TAILLE_DALLE = 50;

    vector<cv::String> fn;
    glob("/home/paviudes/dev/mosaicgiphycpp/data/*.jpg", fn, true);
    // classify all images
    size_t count = fn.size(); // number of png files in images folder
    cout << "nb total d'images : " << count << endl;

    // build empty json dict
    json dict_of_images;
    for (int i = 0; i < 255; i++)
    {
        vector<string> v;
        dict_of_images[i] = v;
    }

    // resize les images et les stocker dans data_output
    Mat img;
    for (size_t i = 0; i < count; i++)
    {
        img = imread(fn[i]);
        cvtColor(img, img, COLOR_RGB2GRAY);
        resize(img, img, Size(TAILLE_DALLE, TAILLE_DALLE));
        Scalar mean = cv::mean(img);
        // save img
        String filePath = "/home/paviudes/dev/mosaicgiphycpp/data_output/image_" + to_string(i) + ".jpg";
        imwrite(filePath, img);

        // update json file
        dict_of_images[mean[0]].push_back(filePath);

        // save json object to file
        string s = dict_of_images.dump();
        ofstream out("/home/paviudes/dev/mosaicgiphycpp/output_small.json");
        out << s;
        out.close();
        cout << i << "/" << count << endl;
    }
}

int main()
{
    processImages();
    return 0;
}